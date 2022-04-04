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

using namespace std;
using namespace libcamera;

class CameraWorker : public QObject
{
    Q_OBJECT

public:
    CameraWorker();

    bool start();

Q_SIGNALS:
    void frameReady();

private:
    bool openCamera();
    bool configureCamera();
    bool startCamera();

private:
    unique_ptr<CameraManager> m_cameraManager;
    shared_ptr<Camera> m_camera;
    unique_ptr<CameraConfiguration> m_configuration;
    map<FrameBuffer *, vector<Span<uint8_t>>> mapped_buffers_;
    map<Stream *, queue<FrameBuffer *>> frame_buffers_;
};
