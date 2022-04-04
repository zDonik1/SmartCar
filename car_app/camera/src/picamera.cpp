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

#include <cameraworker.h>

PICamera::PICamera()
{}

PICamera::~PICamera() {}

bool PICamera::start()
{
    m_worker = make_unique<CameraWorker>();
    m_worker->start();

//    m_worker->moveToThread(&m_captureThread);
//    m_captureThread.start();
//    m_worker->start();

    return true;
}
