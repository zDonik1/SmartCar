/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <iirobstacledetector.h>
#include <iirsensor.h>


class IRObstacleDetector : public IIRObstacleDetector
{
public:
    IRObstacleDetector(std::unique_ptr<IIRSensor> leftSensor,
                       std::unique_ptr<IIRSensor> rightSensor,
                       QObject *parent = nullptr);

    virtual void start() override;
    virtual void stop() override;
    virtual const Vector &vector() const override;

private slots:
    void sensorsUpdated();

private:
    std::unique_ptr<IIRSensor> m_leftSensor;
    std::unique_ptr<IIRSensor> m_rightSensor;
    Vector m_vector;
};
