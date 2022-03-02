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

    virtual void start() override;
    virtual void stop() override;
    virtual bool isBlocked() override;

private:
    void setIsBlocked(bool isBlocked);

private:
    int m_pinN;
    QTimer m_timer;
    bool m_isBlocked;
};
