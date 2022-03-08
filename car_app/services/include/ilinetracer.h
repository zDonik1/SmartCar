/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <vector.h>


class ILineTracer : public QObject
{
    Q_OBJECT

public:
    explicit ILineTracer(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual const Vector &vector() const = 0;

signals:
    void vectorChanged();
};
