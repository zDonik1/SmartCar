/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <ussensor.h>

#include <QDebug>

#include <wiringPi.h>

#include "usworker.h"

using namespace std;


USSensor::USSensor(int trigPinN, int echoPinN, QObject *parent)
    : IUSSensor(parent)
    , m_worker(make_unique<USWorker>(trigPinN, echoPinN))
{
    if (wiringPiSetup() < 0) {
        qWarning() << "Wiring PI was not set up!";
        return;
    }

    pinMode(trigPinN, OUTPUT);
    pinMode(echoPinN, INPUT);

    m_worker->moveToThread(&m_thread);

    connect(m_worker.get(), &USWorker::distanceReady, this, [this](float distance) {
        m_distance = distance;
        emit distanceChanged();
    });
}

USSensor::~USSensor()
{
    USSensor::stop();
}

void USSensor::start(int updateInterval)
{
    if (m_isRunning)
        return;

    if (!m_thread.isRunning()) {
        m_thread.start();
    }

    if (updateInterval != 0) {
        m_worker->start(updateInterval);
    } else {
        m_manualRequestMode = true;
    }
    m_isRunning = true;
}

void USSensor::stop()
{
    if (!m_isRunning)
        return;

    m_distance = -1;
    m_isRunning = false;

    m_worker->stop();
    m_thread.quit();
    m_thread.wait();
}

void USSensor::requestReading()
{
    if (m_manualRequestMode && m_isRunning) {
        m_worker->requestDistance();
    }
}

float USSensor::distance() const
{
    return m_distance;
}
