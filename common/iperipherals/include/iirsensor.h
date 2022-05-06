/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <isensor.h>

class IIRSensor : public QObject, public ISensor
{
    Q_OBJECT

public:
    explicit IIRSensor(QObject *parent = nullptr);

    virtual bool isBlocked() const = 0;

Q_SIGNALS:
    void isBlockedChanged();
};
