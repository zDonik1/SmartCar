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
    /** timeout is in milliseconds */
    USWorker(int trigPinN, int echoPinN, int timeout = 100, QObject *parent = nullptr);

    void start();
    void stop();


signals:
    void distanceReady(float distance, QPrivateSignal = {});
    void operate(QPrivateSignal = {});

private slots:
    void requestDistance();

private:
    int m_trigPinN = -1;
    int m_echoPinN = -1;
    int m_timeout = 100; // timeout for getting next distance, ms
    bool m_isRunning = false;
    QElapsedTimer m_elapsedTimer;
};
