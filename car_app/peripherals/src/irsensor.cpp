/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <irsensor.h>

#include <QDebug>

#include <wiringPi.h>

constexpr auto TIMER_INTERVAL = 20; // ms


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

void IRSensor::start()
{
    m_timer.start(TIMER_INTERVAL);
    emit isBlockedChanged();
}

void IRSensor::stop()
{
    m_timer.stop();
    m_isBlocked = false;
}

void IRSensor::requestCheckBlocked()
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
