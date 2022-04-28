/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <picamera.h>

#include <QDebug>

#include <opencv2/imgcodecs.hpp>

#include <cameraworker.h>

PICamera::PICamera(QObject *parent) : ICamera(parent), m_worker(make_unique<CameraWorker>())
{
    connect(m_worker.get(), &CameraWorker::frameReady, this, &PICamera::frameReady);
}

PICamera::~PICamera() {}

bool PICamera::start()
{
    return m_worker->start();
}
