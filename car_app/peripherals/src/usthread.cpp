/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include "usthread.h"

#include <wiringPi.h>

constexpr auto NSECS_TO_SECS = 1'000'000'000;
constexpr auto SPEED_OF_SOUND = 34'300; // cm/s
constexpr auto US_SENSOR_TIMEOUT = 35; // ms
constexpr auto TRIGGER_PREP_TIME = 100; // ms
constexpr auto TRIGGER_ACTIVE_TIME = 10; // us


float travelTime(float elapsedTime)
{
    return elapsedTime / NSECS_TO_SECS / 2; // dividing by 2 due to twice the time travel of sound
}


USThread::USThread(int trigPinN, int echoPinN, QObject *parent)
    : QThread{parent}
    , m_trigPinN(trigPinN)
    , m_echoPinN(echoPinN)
{
}

void USThread::stop()
{
    m_isRunning = false;
}

void USThread::run()
{
    m_isRunning = true;
    while (m_isRunning) {
        digitalWrite(m_trigPinN, LOW);
        msleep(TRIGGER_PREP_TIME);
        digitalWrite(m_trigPinN, HIGH);
        usleep(TRIGGER_ACTIVE_TIME);
        digitalWrite(m_trigPinN, LOW);

        while (digitalRead(m_echoPinN) == LOW)
            ;

        m_elapsedTimer.start();

        while (digitalRead(m_echoPinN) == HIGH)
            ;

        if (m_elapsedTimer.elapsed() > US_SENSOR_TIMEOUT)
            continue;

        emit distanceReady(travelTime(m_elapsedTimer.nsecsElapsed()) * SPEED_OF_SOUND);
    }
}
