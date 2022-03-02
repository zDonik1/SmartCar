/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>
#include <QElapsedTimer>

class USThread : public QThread
{
    Q_OBJECT

public:
    explicit USThread(int trigPinN, int echoPinN, QObject *parent = nullptr);

    void stop();

protected:
    virtual void run() override;

signals:
    void distanceReady(float distance);

private:
    int m_trigPinN = -1;
    int m_echoPinN = -1;
    bool m_isRunning = false;
    QElapsedTimer m_elapsedTimer;
};
