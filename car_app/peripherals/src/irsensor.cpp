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

    m_timer.setInterval(TIMER_INTERVAL);

    connect(&m_timer, &QTimer::timeout, this, [this]{ setIsBlocked(digitalRead(m_pinN) == LOW); });
}

void IRSensor::start()
{
    m_timer.start();
    emit isBlockedChanged();
}

void IRSensor::stop()
{
    m_timer.stop();
    m_isBlocked = false;
}

bool IRSensor::isBlocked()
{
    return m_isBlocked;
}

void IRSensor::setIsBlocked(bool isBlocked)
{
    if (m_isBlocked != isBlocked) {
        m_isBlocked = isBlocked;
        emit isBlockedChanged();
    }
}
