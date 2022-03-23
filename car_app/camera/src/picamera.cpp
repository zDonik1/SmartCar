/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <picamera.h>

#include <string>

#include <QDebug>

#include <libcamera/camera_manager.h>
#include <libcamera/camera.h>
#include <libcamera/framebuffer_allocator.h>

#include <cameraworker.h>

using namespace std;
using namespace libcamera;

constexpr int DEFAULT_CAMERA = 0;


PICamera::PICamera()
    : m_cameraManager(make_unique<CameraManager>())
{}

PICamera::~PICamera() {}

bool PICamera::start()
{
    if (!openCamera())
        return false;

    if (!configureCamera())
        return false;

    if (!startCamera())
        return false;

    m_worker = make_unique<CameraWorker>(*m_camera);
//    m_worker->moveToThread(&m_captureThread);
//    m_captureThread.start();
//    m_worker->start();

    return true;
}

bool PICamera::openCamera()
{
    if (!m_cameraManager->start()) {
        qWarning() << "Couldn't start CameraManager!";
        return false;
    }

    if (m_cameraManager->cameras().size() == 0) {
        qWarning() << "No cameras available";
        return false;
    }

    m_camera = m_cameraManager->cameras()[DEFAULT_CAMERA];

    if (!m_camera) {
        qWarning() << "Couldn't find default camera";
        return false;
    }

    if (m_camera->acquire()) {
        qWarning() << "Couldn't acquire camera";
        return false;
    }

    qDebug() << "Acquired camera" << QString::fromStdString(m_camera->id());
    return true;
}

bool PICamera::configureCamera()
{
    // configuring camera

    m_configuration = m_camera->generateConfiguration({StreamRole::VideoRecording});
    if (!m_configuration) {
        qWarning() << "Couldn't generate VideoRecording default config for camera";
        return false;
    }

    if (m_configuration->validate() == CameraConfiguration::Invalid) {
        qWarning() << "Camera configuration is invalid";
        return false;
    }

    if (m_camera->configure(m_configuration.get()) < 0) {
        qWarning() << "Couldn't configure camera";
        return false;
    }


    // allocating buffers

    FrameBufferAllocator allocator_ {m_camera};
    for (StreamConfiguration &config : *m_configuration)
    {
        Stream *stream = config.stream();

        if (allocator_.allocate(stream) < 0)
            throw std::runtime_error("failed to allocate capture buffers");

        for (const std::unique_ptr<FrameBuffer> &buffer : allocator_.buffers(stream))
        {
            // "Single plane" buffers appear as multi-plane here, but we can spot them because then
            // planes all share the same fd. We accumulate them so as to mmap the buffer only once.
            size_t buffer_size = 0;
            for (unsigned i = 0; i < buffer->planes().size(); i++)
            {
                const FrameBuffer::Plane &plane = buffer->planes()[i];
                buffer_size += plane.length;
                if (i == buffer->planes().size() - 1 || plane.fd.get() != buffer->planes()[i + 1].fd.get())
                {
                    void *memory = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, plane.fd.get(), 0);
                    mapped_buffers_[buffer.get()].push_back(
                        libcamera::Span<uint8_t>(static_cast<uint8_t *>(memory), buffer_size));
                    buffer_size = 0;
                }
            }
            frame_buffers_[stream].push(buffer.get());
        }
    }

    return true;
}

bool PICamera::startCamera()
{
    return true;
}
