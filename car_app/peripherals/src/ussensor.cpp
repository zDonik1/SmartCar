/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <ussensor.h>

#include <QDebug>

#include <wiringPi.h>

#include "usthread.h"

using namespace std;


USSensor::USSensor(int trigPinN, int echoPinN, QObject *parent)
    : IUSSensor(parent)
    , m_thread(make_unique<USThread>(trigPinN, echoPinN))
{
    if (wiringPiSetup() < 0) {
        qWarning() << "Wiring PI was not set up!";
        return;
    }

    pinMode(trigPinN, OUTPUT);
    pinMode(echoPinN, INPUT);

    connect(m_thread.get(), &USThread::distanceReady, this, &USSensor::onDistanceReady);
}

USSensor::~USSensor() {}

void USSensor::start()
{
    m_thread->start();
}

void USSensor::stop()
{
    m_thread->stop();
    m_thread->wait();
}

float USSensor::distance()
{
    return m_distance;
}

void USSensor::setThreshold(float threshold)
{
    m_threshold = threshold;
}

void USSensor::onDistanceReady(float distance)
{
    m_previousDistance = m_distance;
    m_distance = distance;

    if (m_threshold > 0 && m_previousDistance > 0) {
        if (m_distance < m_threshold && m_previousDistance > m_threshold) {
            emit thresholdCrossed(true);
        } else if (m_distance > m_threshold && m_previousDistance < m_threshold) {
            emit thresholdCrossed(false);
        }
    }
}
