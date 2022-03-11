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


float travelTime(float elapsedTime)
{
    return elapsedTime / NSECS_TO_SECS / 2; // dividing by 2 due to twice the time travel of sound
}


USWorker::USWorker(int trigPinN, int echoPinN, int timeout, QObject *parent)
    : QObject{parent}, m_trigPinN(trigPinN), m_echoPinN(echoPinN), m_timeout(timeout)
{
    connect(this, &USWorker::startAsync, this, &USWorker::findDistanceContinuous, Qt::QueuedConnection);
    connect(this, &USWorker::requestDistanceSignal, this, &USWorker::findDistanceOnce, Qt::QueuedConnection);
}

void USWorker::start()
{
    m_isRunning.store(true);
    emit startAsync();
}

void USWorker::stop()
{
    m_isRunning.store(false);
}

void USWorker::requestDistance()
{
    emit requestDistanceSignal();
}

std::pair<float, bool> USWorker::calculateDistance()
{
    digitalWrite(m_trigPinN, LOW);
    QThread::msleep(TRIGGER_PREP_TIME);
    digitalWrite(m_trigPinN, HIGH);
    QThread::usleep(TRIGGER_ACTIVE_TIME);
    digitalWrite(m_trigPinN, LOW);

    m_elapsedTimer.start();
    while (digitalRead(m_echoPinN) == LOW && m_elapsedTimer.elapsed() < US_SENSOR_TIMEOUT)
        ;

    if (m_elapsedTimer.elapsed() >= US_SENSOR_TIMEOUT)
        return {-1, false};

    m_elapsedTimer.start();
    while (digitalRead(m_echoPinN) == HIGH && m_elapsedTimer.elapsed() < US_SENSOR_TIMEOUT)
        ;

    if (m_elapsedTimer.elapsed() >= US_SENSOR_TIMEOUT)
        return {-1, false};

    return {travelTime(m_elapsedTimer.nsecsElapsed()) * SPEED_OF_SOUND, true};
}

void USWorker::findDistanceOnce()
{
    auto [distance, success] = calculateDistance();
    if (success) {
        emit distanceReady(distance);
    }
}

void USWorker::findDistanceContinuous()
{
    if (!m_isRunning)
        return;

    findDistanceOnce();
    QTimer::singleShot(m_timeout, this, &USWorker::findDistanceContinuous);
}
