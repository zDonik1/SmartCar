/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <irsensor.h>

#include <QDebug>

#include <wiringPi.h>


IRSensor::IRSensor(int pinN, QObject *parent)
    : IIRSensor(parent)
{
    if (wiringPiSetup() < 0) {
        qWarning() << "Wiring PI was not set up!";
        return;
    }

    m_pinN = pinN;

    pinMode(m_pinN, INPUT);

    connect(&m_timer, &QTimer::timeout, this, &IRSensor::updateIsBlocked);
}

void IRSensor::start(int updateInterval)
{
    if (m_isRunning)
        return;

    if (updateInterval != 0) {
        m_timer.start(updateInterval);
    } else {
        m_manualRequestMode = true;
    }
    m_isRunning = true;
}

void IRSensor::stop()
{
    if (!m_isRunning)
        return;

    m_isBlocked = false;
    m_isRunning = false;
    m_manualRequestMode = false;

    m_timer.stop();
}

void IRSensor::requestReading()
{
    updateIsBlocked();
}

bool IRSensor::isBlocked() const
{
    return m_isBlocked;
}

void IRSensor::updateIsBlocked()
{
    setIsBlocked(readIsBlocked());
}

void IRSensor::setIsBlocked(bool isBlocked)
{
    if (m_isBlocked != isBlocked) {
        m_isBlocked = isBlocked;
        emit isBlockedChanged();
    }
}

bool IRSensor::readIsBlocked() const
{
    return digitalRead(m_pinN) == LOW;
}
