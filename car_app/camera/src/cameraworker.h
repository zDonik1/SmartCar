/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#pragma once

#include <queue>

#include <QObject>

#include <opencv2/core.hpp>

#include <libcamera/base/span.h>
#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/framebuffer_allocator.h>

#include <frame.h>

using namespace std;
using namespace libcamera;
using namespace cv;

class CameraWorker : public QObject
{
    Q_OBJECT

public:
    explicit CameraWorker(QObject *parent = nullptr);

    bool start();

Q_SIGNALS:
    void frameReady(FramePtr frame);

private:
    bool openCamera();
    bool configureCamera();
    bool startCamera();

    bool makeRequests();
    void requestComplete(Request *request);
    void queueRequest(Frame *frame);

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

    bool m_cameraStarted = false;
    uint64_t m_sequence = 0;
    uint64_t m_lastTimestamp;
};
