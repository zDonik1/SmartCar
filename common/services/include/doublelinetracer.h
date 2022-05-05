/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <avoider.h>
#include <iirsensor.h>


class DoubleLineTracer : public Avoider
{
public:
    DoubleLineTracer(std::shared_ptr<IIRSensor> leftSensor,
                     std::shared_ptr<IIRSensor> rightSensor,
                     QObject *parent = nullptr);

private slots:
    void sensorsUpdated();

private:
    std::shared_ptr<IIRSensor> m_leftSensor;
    std::shared_ptr<IIRSensor> m_rightSensor;
};
