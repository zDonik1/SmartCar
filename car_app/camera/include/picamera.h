/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>

#include <icamera.h>

class CameraWorker;

class PICamera : public QObject, public ICamera
{
public:
    explicit PICamera(QObject *parent = nullptr);
    virtual ~PICamera();

    virtual bool start() override;

private:
    std::unique_ptr<CameraWorker> m_worker;
    QThread m_captureThread;
    bool once = false;
};
