/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#include <cameraworker.h>

#include <QDebug>

#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;


CameraWorker::CameraWorker(libcamera::Camera &camera)
    : m_camera(camera)
{}

CameraWorker::~CameraWorker() {}

void CameraWorker::start()
{
    captureFrame();
}

void CameraWorker::captureFrame()
{
//    qDebug() << m_capture.grab();
//    if (!m_capture.read(*m_frame)) {
//        qDebug() << "Couldn't grab frame!";
//        return;
//    }

//    imwrite("/tmp/capture.jpg", *m_frame);
}
