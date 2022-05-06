/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QTimer>

#include <iirsensor.h>


class IRSensor : public IIRSensor
{
    Q_OBJECT

public:
    explicit IRSensor(int pinN, QObject *parent = nullptr);

    virtual void start(int updateInterval) override;
    virtual void stop() override;

    virtual void requestReading() override;
    virtual bool isBlocked() const override;

private Q_SLOTS:
    void updateIsBlocked();

private:
    void setIsBlocked(bool isBlocked);
    bool readIsBlocked() const;

private:
    int m_pinN = -1;
    QTimer m_timer;
    bool m_isBlocked = false;
    bool m_isRunning = false;
    bool m_manualRequestMode = false;
};
