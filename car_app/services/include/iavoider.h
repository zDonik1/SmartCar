/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 07/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <vector.h>


class IAvoider : public QObject
{
    Q_OBJECT

public:
    explicit IAvoider(QObject *parent = nullptr) : QObject(parent) {}

    virtual const Vector &vector() const = 0;
    virtual bool isBlocked() const = 0;

signals:
    void vectorChanged(QPrivateSignal = {});
    void isBlockedChanged(QPrivateSignal = {});
};
