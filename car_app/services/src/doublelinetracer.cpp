/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#include <doublelinetracer.h>

#include <QDebug>

using namespace std;


DoubleLineTracer::DoubleLineTracer(std::shared_ptr<IIRSensor> leftSensor,
                                   std::shared_ptr<IIRSensor> rightSensor,
                                   QObject *parent)
    : IAvoider(parent), m_leftSensor(leftSensor), m_rightSensor(rightSensor)
{
    connect(m_leftSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &DoubleLineTracer::sensorsUpdated);

    connect(m_rightSensor.get(),
            &IIRSensor::isBlockedChanged,
            this,
            &DoubleLineTracer::sensorsUpdated);
}

const Vector &DoubleLineTracer::vector() const
{
    return m_vector;
}

bool DoubleLineTracer::isBlocked() const
{
    return m_isBlocked;
}

void DoubleLineTracer::sensorsUpdated()
{
    if (m_leftSensor->isBlocked() && m_rightSensor->isBlocked()) {
        setVector({0, 0});
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

void DoubleLineTracer::setVector(Vector vector)
{
    if (m_vector != vector) {
        m_vector = vector;
        emit vectorChanged();
    }
}

void DoubleLineTracer::setIsBlocked(bool isBlocked)
{
    if (m_isBlocked != isBlocked) {
        m_isBlocked = isBlocked;
        emit isBlockedChanged();
    }
}
