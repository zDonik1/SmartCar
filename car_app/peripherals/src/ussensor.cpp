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

constexpr auto REQUEST_INTERVAL = 10; // ms


USSensor::USSensor(int trigPinN, int echoPinN, QObject *parent)
    : IUSSensor(parent)
    , m_worker(make_unique<USWorker>(trigPinN, echoPinN, REQUEST_INTERVAL))
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

USSensor::~USSensor() {}

void USSensor::start()
{
    if (!m_thread.isRunning()) {
        m_thread.start();
    }
    m_worker->start();
}

void USSensor::pause()
{
    m_worker->stop();
}

void USSensor::stop()
{
    m_worker->stop();
    m_thread.quit();
    m_thread.wait();
}

float USSensor::distance() const
{
    return m_distance;
}
