/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <lccamera.h>

#include <mutex>
#include <queue>

#include <QDebug>

#include <sys/mman.h>
#include <libcamera/base/span.h>
#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/framebuffer_allocator.h>
#include <libcamera/control_ids.h>
#include <libcamera/formats.h>

using namespace std;
using namespace libcamera;
using namespace cv;

constexpr auto NANOSEC_IN_SEC = 1e9;
constexpr auto BUFFER_COUNT = 6;


// ==== PImpl ==============================================================

class LCCamera::PImpl
{
public:
    explicit PImpl(LCCamera *pubImpl)
        : pubImpl(pubImpl), m_controls(controls::controls)
    {}
    ~PImpl() { pubImpl->stop(); }

public:
    bool openCamera();
    bool configureCamera();
    bool startCamera();

    void stopCamera();
    void teardown();
    void closeCamera();

private:
    bool makeRequests();
    void requestComplete(Request *request);
    void queueRequest(Frame *frame);

public:
    LCCamera *pubImpl;
    unsigned int cameraIndex = 0;
    unsigned int captureHeight = 0;
    unsigned int captureWidth = 0;

private:
    CameraManager m_cameraManager;
    shared_ptr<Camera> m_camera;
    unique_ptr<CameraConfiguration> m_configuration;
    unique_ptr<FrameBufferAllocator> m_allocator;
    map<FrameBuffer *, vector<Span<uint8_t>>> m_mappedBuffers;
    map<Stream *, queue<FrameBuffer *>> m_frameBuffers;
    vector<unique_ptr<Request>> m_requests;
    map<Frame *, Request *> m_frameRequests;
    ControlList m_controls;

    mutex m_frameMutex;
    mutex m_cameraStopMutex;
    mutex m_controlMutex;

    bool m_cameraAcquired = false;
    bool m_cameraStarted = false;
    SequenceType m_sequence = 0;
    uint64_t m_lastTimestamp;
};

bool LCCamera::PImpl::openCamera()
{
    int code = m_cameraManager.start();
    if (code != 0) {
        qWarning() << "Couldn't start CameraManager. Code:" << code;
        return false;
    }

    if (m_cameraManager.cameras().size() == 0) {
        qWarning() << "No cameras available";
        return false;
    }

    m_camera = m_cameraManager.cameras()[cameraIndex];
    if (!m_camera) {
        qWarning() << "Couldn't find default camera";
        return false;
    }

    if (m_camera->acquire()) {
        qWarning() << "Couldn't acquire camera";
        return false;
    }
    m_cameraAcquired = true;

    qDebug() << "Acquired camera" << QString::fromStdString(m_camera->id());
    return true;
}

bool LCCamera::PImpl::configureCamera()
{
    // configuring camera

    m_configuration = m_camera->generateConfiguration({StreamRole::VideoRecording});
    if (!m_configuration) {
        qWarning() << "Couldn't generate VideoRecording default config for camera";
        return false;
    }

    auto &config = m_configuration->at(0);
    config.pixelFormat = formats::RGB888;
    config.size.height = captureHeight;
    config.size.width = captureWidth;
    config.bufferCount = BUFFER_COUNT; // 6 buffers is better than 4

    if (m_configuration->validate() == CameraConfiguration::Invalid) {
        qWarning() << "Camera configuration is invalid";
        return false;
    }

    if (m_camera->configure(m_configuration.get()) < 0) {
        qWarning() << "Couldn't configure camera";
        return false;
    }


    // allocating buffers

    m_allocator = make_unique<FrameBufferAllocator>(m_camera);
    for (auto &config : *m_configuration) {
        auto stream = config.stream();

        if (m_allocator->allocate(stream) < 0) {
            qWarning() << "Failed to allocate capture buffers";
            return false;
        }

        for (const auto &buffer : m_allocator->buffers(stream)) {
            // "Single plane" buffers appear as multi-plane here, but we can spot them because then
            // planes all share the same fd. We accumulate them so as to mmap the buffer only once.
            size_t bufferSize = 0;
            for (unsigned i = 0; i < buffer->planes().size(); i++) {
                auto &plane = buffer->planes()[i];
                bufferSize += plane.length;
                if (i == buffer->planes().size() - 1
                    || plane.fd.get() != buffer->planes()[i + 1].fd.get()) {
                    auto memory = mmap(NULL,
                                       bufferSize,
                                       PROT_READ | PROT_WRITE,
                                       MAP_SHARED,
                                       plane.fd.get(),
                                       0);
                    m_mappedBuffers[buffer.get()].push_back(
                        libcamera::Span<uint8_t>(static_cast<uint8_t *>(memory), bufferSize));
                    bufferSize = 0;
                }
            }
            m_frameBuffers[stream].push(buffer.get());
        }
    }

    return true;
}

bool LCCamera::PImpl::startCamera()
{
    if (!makeRequests())
        return false;

    if (m_camera->start(&m_controls)) {
        qWarning() << "Failed to start camera!";
        return false;
    }

    m_controls.clear();
    m_cameraStarted = true;
    m_lastTimestamp = 0;
    m_camera->requestCompleted.connect(this, &PImpl::requestComplete);

    for (auto &request : m_requests) {
        if (m_camera->queueRequest(request.get()) < 0) {
            qWarning() << "Failed to queue request in startCamera";
            return false;
        }
    }

    return true;
}

void LCCamera::PImpl::stopCamera()
{
    {
        // We don't want QueueRequest to run asynchronously while we stop the camera.
        lock_guard<mutex> lock(m_cameraStopMutex);
        if (m_cameraStarted) {
            if (m_camera->stop())
                throw std::runtime_error("failed to stop camera");

            m_cameraStarted = false;
        }
    }

    if (m_camera)
        m_camera->requestCompleted.disconnect(this, &PImpl::requestComplete);

    // An application might be holding a CompletedRequest, so queueRequest will get
    // called to delete it later, but we need to know not to try and re-queue it.
    m_frameRequests.clear();
    m_requests.clear();
    m_controls.clear(); // no need for mutex here
}

void LCCamera::PImpl::teardown()
{
    for (auto &keyValue : m_mappedBuffers) {
        for (auto &span : keyValue.second)
            munmap(span.data(), span.size());
    }
    m_mappedBuffers.clear();

    m_allocator.reset();
    m_configuration.reset();
    m_frameBuffers.clear();
}

void LCCamera::PImpl::closeCamera()
{
    if (m_cameraAcquired)
        m_camera->release();
    m_cameraAcquired = false;

    m_camera.reset();
}

bool LCCamera::PImpl::makeRequests()
{
    auto freeBuffers(m_frameBuffers);
    while (true)
    {
        for (const auto &config : *m_configuration)
        {
            const auto stream = config.stream();
            if (stream == m_configuration->at(0).stream())
            {
                if (freeBuffers[stream].empty())
                    return true;

                auto request = m_camera->createRequest();
                if (!request) {
                    qWarning() << "Failed to make request.";
                    return false;
                }
                m_requests.push_back(std::move(request));
            } else if (freeBuffers[stream].empty()) {
                qWarning() << "Concurrent streams need matching numbers of buffers.";
                return false;
            }

            FrameBuffer *buffer = freeBuffers[stream].front();
            freeBuffers[stream].pop();
            if (m_requests.back()->addBuffer(stream, buffer) < 0) {
                qWarning() << "Failed to add buffer to request.";
                return false;
            }
        }
    }
}

void LCCamera::PImpl::requestComplete(Request *request)
{
    if (request->status() == Request::RequestCancelled)
        return;

    auto stream = m_configuration->at(0).stream();
    auto config = stream->configuration();
    auto itr = m_mappedBuffers.find(request->buffers().at(stream));
    auto buffer = itr == end(m_mappedBuffers) ? Span<uint8_t>() : itr->second[0];
    auto frame = new Frame(m_sequence++,
                           Mat(config.size.height,
                               config.size.width,
                               CV_8UC3,
                               buffer.data(),
                               config.stride));
    FramePtr payload(frame, [this](Frame *frame) { queueRequest(frame); });

    {
        lock_guard<mutex> lock(m_frameMutex);
        m_frameRequests[frame] = request;
    }

    // We calculate the instantaneous framerate in case anyone wants it.
    uint64_t timestamp = request->buffers().begin()->second->metadata().timestamp;
    if (m_lastTimestamp == 0 || m_lastTimestamp == timestamp)
        payload->framerate = 0;
    else
        payload->framerate = NANOSEC_IN_SEC / (timestamp - m_lastTimestamp);
    m_lastTimestamp = timestamp;

    Q_EMIT pubImpl->frameReady(payload);
}

void LCCamera::PImpl::queueRequest(Frame *frame)
{
    // This function may run asynchronously so needs protection from the
    // camera stopping at the same time.
    lock_guard<mutex> stop_lock(m_cameraStopMutex);
    if (!m_cameraStarted)
        return;

    Request *request = nullptr;
    {
        // An application could be holding a CompletedRequest while it stops and re-starts
        // the camera, after which we don't want to queue another request now.
        lock_guard<mutex> lock(m_frameMutex);

        auto itr = m_frameRequests.find(frame);
        if (itr == end(m_frameRequests) || !itr->second)
            return;

        request = itr->second;

        delete frame;
        m_frameRequests.erase(itr);
    }

    request->reuse(Request::ReuseBuffers);

    {
        lock_guard<mutex> lock(m_controlMutex);
        request->controls() = move(m_controls);
    }

    if (m_camera->queueRequest(request) < 0)
        qWarning() << "Failed to queue request";
}


// ==== LCCamera ==============================================================

LCCamera::LCCamera(unsigned int cameraIndex,
                   unsigned int captureHeight,
                   unsigned int captureWidth,
                   QObject *parent)
    : ICamera(parent), m_pimpl(make_unique<PImpl>(this))
{
    m_pimpl->cameraIndex = cameraIndex;
    m_pimpl->captureHeight = captureHeight;
    m_pimpl->captureWidth = captureWidth;
}

LCCamera::~LCCamera() {}

bool LCCamera::start()
{
    if (!m_pimpl->openCamera())
        return false;

    if (!m_pimpl->configureCamera())
        return false;

    if (!m_pimpl->startCamera())
        return false;

    return true;
}

void LCCamera::stop()
{
    m_pimpl->stopCamera();
    m_pimpl->teardown();
    m_pimpl->closeCamera();
}
