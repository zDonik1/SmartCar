/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#include <doublelinetracer.h>

#include <QDebug>

using namespace std;


DoubleLineTracer::DoubleLineTracer(std::unique_ptr<IIRSensor> leftSensor,
                                   std::unique_ptr<IIRSensor> rightSensor,
                                   QObject *parent)
    : ILineTracer(parent), m_leftSensor(move(leftSensor)), m_rightSensor(move(rightSensor))
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

void DoubleLineTracer::start()
{
    m_leftSensor->start();
    m_rightSensor->start();
}

void DoubleLineTracer::stop()
{
    m_leftSensor->stop();
    m_rightSensor->stop();
}

const Vector &DoubleLineTracer::vector() const
{
    return m_vector;
}

void DoubleLineTracer::sensorsUpdated()
{
    if (m_leftSensor->isBlocked() && m_rightSensor->isBlocked()) {
        // big brah moment
        qDebug() << "both sensors touched line, not sure what to do";
        m_vector = {0, 0};
    } else if (m_leftSensor->isBlocked()) {
        m_vector = {1, 0};
    } else if (m_rightSensor->isBlocked()) {
        m_vector = {-1, 0};
    } else {
        m_vector = {0, 1};
    }
    emit vectorChanged();
}