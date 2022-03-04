/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include "usworker.h"

#include <QTimer>
#include <QDebug>

#include <wiringPi.h>

constexpr auto NSECS_TO_SECS = 1'000'000'000;
constexpr auto SPEED_OF_SOUND = 34'300; // cm/s
constexpr auto US_SENSOR_TIMEOUT = 35; // ms
constexpr auto TRIGGER_PREP_TIME = 10; // ms
constexpr auto TRIGGER_ACTIVE_TIME = 10; // us
constexpr auto COUNTER_TIMEOUT = 5000;


float travelTime(float elapsedTime)
{
    return elapsedTime / NSECS_TO_SECS / 2; // dividing by 2 due to twice the time travel of sound
}


USWorker::USWorker(int trigPinN, int echoPinN, int timeout, QObject *parent)
    : QObject{parent}, m_trigPinN(trigPinN), m_echoPinN(echoPinN), m_timeout(timeout)
{
    connect(this, &USWorker::operate, this, &USWorker::requestDistance, Qt::QueuedConnection);
}

void USWorker::start()
{
    m_isRunning = true;
    emit operate();
}

void USWorker::stop()
{
    m_isRunning = false;
}

void USWorker::requestDistance()
{
    // help functions

    static const auto requestDistance = [this] {
        QTimer::singleShot(m_timeout, this, &USWorker::requestDistance);
    };


    // business logic

    if (!m_isRunning)
        return;

    digitalWrite(m_trigPinN, LOW);
    QThread::msleep(TRIGGER_PREP_TIME);
    digitalWrite(m_trigPinN, HIGH);
    QThread::usleep(TRIGGER_ACTIVE_TIME);
    digitalWrite(m_trigPinN, LOW);

    int counter = 0;
    while (digitalRead(m_echoPinN) == LOW && counter < COUNTER_TIMEOUT) {
        ++counter;
    }

    if (counter >= COUNTER_TIMEOUT) {
        requestDistance();
        return;
    }

    m_elapsedTimer.start();

    counter = 0;
    while (digitalRead(m_echoPinN) == HIGH && counter < COUNTER_TIMEOUT) {
        ++counter;
    }

    if (counter >= COUNTER_TIMEOUT) {
        requestDistance();
        return;
    }

    if (m_elapsedTimer.elapsed() > US_SENSOR_TIMEOUT)
        return;

    emit distanceReady(travelTime(m_elapsedTimer.nsecsElapsed()) * SPEED_OF_SOUND);
    requestDistance();
}
