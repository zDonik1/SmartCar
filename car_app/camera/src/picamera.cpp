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

PICamera::PICamera(QObject *parent) : QObject(parent) {}

PICamera::~PICamera() {}

bool PICamera::start()
{
    m_worker = make_unique<CameraWorker>();
    connect(m_worker.get(), &CameraWorker::frameReady, this, [this] {
        if (once)
            return;

        qDebug() << imwrite("output.png", m_worker->nextFrame()->image);
        once = true;
    });
    return m_worker->start();

//    m_worker->moveToThread(&m_captureThread);
//    m_captureThread.start();
//    m_worker->start();
}
