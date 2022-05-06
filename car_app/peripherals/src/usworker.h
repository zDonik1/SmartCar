/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>
#include <QElapsedTimer>

class USWorker : public QObject
{
    Q_OBJECT

public:
    USWorker(int trigPinN, int echoPinN, QObject *parent = nullptr);

    void start(int updateInterval);
    void stop();
    void requestDistance();

Q_SIGNALS:
    void distanceReady(float distance, QPrivateSignal = {});
    void startAsync(QPrivateSignal = {});
    void requestDistanceSignal(QPrivateSignal = {});

private Q_SLOTS:
    void findDistanceOnce();
    void findDistanceContinuous();

private:
    /**
     *  @brief It is a blocking function that calculates the distance.
     *  @return Returns a pair of distance and success.
     */
    std::pair<float, bool> calculateDistance();

private:
    int m_trigPinN = -1;
    int m_echoPinN = -1;
    int m_updateInterval = 100; // timeout for getting next distance, ms
    std::atomic_bool m_isRunning = false;
    QElapsedTimer m_elapsedTimer;
};
