/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#include <cameraworker.h>

#include <QDebug>

#include <sys/mman.h>
#include <libcamera/framebuffer_allocator.h>

constexpr auto DEFAULT_CAMERA = 0;

CameraWorker::CameraWorker()
{}

bool CameraWorker::start()
{
    if (!openCamera())
        return false;

    if (!configureCamera())
        return false;

    if (!startCamera())
        return false;

    return true;
}

bool CameraWorker::openCamera()
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

bool CameraWorker::configureCamera()
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

    FrameBufferAllocator allocator_{m_camera};
    for (StreamConfiguration &config : *m_configuration) {
        Stream *stream = config.stream();

        if (allocator_.allocate(stream) < 0)
            throw std::runtime_error("failed to allocate capture buffers");

        for (const std::unique_ptr<FrameBuffer> &buffer : allocator_.buffers(stream)) {
            // "Single plane" buffers appear as multi-plane here, but we can spot them because then
            // planes all share the same fd. We accumulate them so as to mmap the buffer only once.
            size_t buffer_size = 0;
            for (unsigned i = 0; i < buffer->planes().size(); i++) {
                const FrameBuffer::Plane &plane = buffer->planes()[i];
                buffer_size += plane.length;
                if (i == buffer->planes().size() - 1
                    || plane.fd.get() != buffer->planes()[i + 1].fd.get()) {
                    void *memory = mmap(NULL,
                                        buffer_size,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED,
                                        plane.fd.get(),
                                        0);
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

bool CameraWorker::startCamera()
{
    return true;
}
