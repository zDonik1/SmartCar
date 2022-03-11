/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>


class IIRSensor : public QObject
{
    Q_OBJECT

public:
    explicit IIRSensor(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void requestCheckBlocked() = 0;
    virtual bool isBlocked() const = 0;

signals:
    void isBlockedChanged();
};
