/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <irobstacledetector.h>

using namespace std;

IRObstacleDetector::IRObstacleDetector(std::unique_ptr<IIRSensor> leftSensor,
                                       std::unique_ptr<IIRSensor> rightSensor,
                                       QObject *parent)
    : IIRObstacleDetector(parent), m_leftSensor(move(leftSensor)), m_rightSensor(move(rightSensor))
{
    connect(m_leftSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &IRObstacleDetector::sensorsUpdated);

    connect(m_rightSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &IRObstacleDetector::sensorsUpdated);
}

void IRObstacleDetector::start()
{
    m_leftSensor->start();
    m_rightSensor->start();
}

void IRObstacleDetector::stop()
{
    m_leftSensor->stop();
    m_rightSensor->stop();
    m_vector = {0, 0};
}

const Vector &IRObstacleDetector::vector() const
{
    return m_vector;
}

void IRObstacleDetector::sensorsUpdated()
{
    if (m_leftSensor->isBlocked() && m_rightSensor->isBlocked()) {
        setVector({0, -1});
    } else if (m_leftSensor->isBlocked()) {
        setVector({1, 0});
    } else if (m_rightSensor->isBlocked()) {
        setVector({-1, 0});
    } else {
        setVector({0, 1});
    }
}

void IRObstacleDetector::setVector(Vector vector)
{
    if (m_vector != vector) {
        m_vector = vector;
        emit vectorChanged();
    }
}
