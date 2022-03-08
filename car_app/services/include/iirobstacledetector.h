/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 07/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <vector.h>


class IIRObstacleDetector : public QObject
{
    Q_OBJECT

public:
    explicit IIRObstacleDetector(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual const Vector &vector() const = 0;

signals:
    void vectorChanged();
};
