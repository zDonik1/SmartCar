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
    : Avoider(parent), m_leftSensor(leftSensor), m_rightSensor(rightSensor)
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
