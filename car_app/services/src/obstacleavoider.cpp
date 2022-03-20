/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <obstacleavoider.h>

using namespace std;

ObstacleAvoider::ObstacleAvoider(std::shared_ptr<IIRSensor> leftSensor,
                                 std::shared_ptr<IIRSensor> rightSensor,
                                 QObject *parent)
    : Avoider(parent), m_leftSensor(leftSensor), m_rightSensor(rightSensor)
{
    connect(m_leftSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &ObstacleAvoider::sensorsUpdated);

    connect(m_rightSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &ObstacleAvoider::sensorsUpdated);
}

void ObstacleAvoider::sensorsUpdated()
{
    if (m_leftSensor->isBlocked() && m_rightSensor->isBlocked()) {
        setVector({0, -1});
        setIsBlocked(true);
    } else if (m_leftSensor->isBlocked()) {
        setVector({1, 0});
        setIsBlocked(true);
    } else if (m_rightSensor->isBlocked()) {
        setVector({-1, 0});
        setIsBlocked(true);
    } else {
        setVector({0, 1});
        setIsBlocked(false);
    }
}
