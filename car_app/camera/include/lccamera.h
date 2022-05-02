/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <icamera.h>

class LCCamera final : public ICamera
{
    Q_OBJECT

public:
    explicit LCCamera(unsigned int cameraIndex, QObject *parent = nullptr);
    virtual ~LCCamera();

    bool start() override;
    void stop() override;

private:
    class PImpl;
    std::unique_ptr<PImpl> m_pimpl;
};
