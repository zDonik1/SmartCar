/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#pragma once

#include <opencv2/core.hpp>
#include <libcamera/camera.h>

#include <QObject>

class CameraWorker : public QObject
{
    Q_OBJECT

public:
    CameraWorker(libcamera::Camera &camera);
    virtual ~CameraWorker();

    void start();

signals:
    void frameReady();

private slots:
    void captureFrame();

private:
    libcamera::Camera &m_camera;
    cv::Mat m_frame;
};
