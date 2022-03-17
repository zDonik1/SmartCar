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
    : IAvoider(parent), m_leftSensor(leftSensor), m_rightSensor(rightSensor)
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

const Vector &ObstacleAvoider::vector() const
{
    return m_vector;
}

bool ObstacleAvoider::isBlocked() const
{
    return m_isBlocked;
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

void ObstacleAvoider::setVector(Vector vector)
{
    if (m_vector != vector) {
        m_vector = vector;
        emit vectorChanged();
    }
}

void ObstacleAvoider::setIsBlocked(bool isBlocked)
{
    if (m_isBlocked != isBlocked) {
        m_isBlocked = isBlocked;
        emit isBlockedChanged();
    }
}
