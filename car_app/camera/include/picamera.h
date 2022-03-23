/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>

#include <icamera.h>

namespace libcamera {
class CameraManager;
class Camera;
class CameraConfiguration;
} // namespace libcamera

class CameraWorker;


class PICamera : public ICamera
{
public:
    PICamera();
    virtual ~PICamera();

    virtual bool start() override;

private:
    bool openCamera();
    bool configureCamera();
    bool startCamera();

private:
    std::unique_ptr<libcamera::CameraManager> m_cameraManager;
    std::shared_ptr<libcamera::Camera> m_camera;
    std::unique_ptr<libcamera::CameraConfiguration> m_configuration;
    std::unique_ptr<CameraWorker> m_worker;
    QThread m_captureThread;
};
