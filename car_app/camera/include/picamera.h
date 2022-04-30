/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <imageprocessor.h>

class CameraWorker;

class PICamera final : public ICamera
{
    Q_OBJECT

public:
    explicit PICamera(QObject *parent = nullptr);
    virtual ~PICamera();

    bool start() override;
    void stop() override;

private:
    std::unique_ptr<CameraWorker> m_worker;
};
