/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <avoider.h>
#include <iirsensor.h>


class ObstacleAvoider : public Avoider
{
public:
    ObstacleAvoider(std::shared_ptr<IIRSensor> leftSensor,
                         std::shared_ptr<IIRSensor> rightSensor,
                         QObject *parent = nullptr);

private slots:
    void sensorsUpdated();

private:
    std::shared_ptr<IIRSensor> m_leftSensor;
    std::shared_ptr<IIRSensor> m_rightSensor;
};
