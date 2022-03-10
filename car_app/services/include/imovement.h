/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <vector.h>

class IMovement : public QObject
{
    Q_OBJECT

public:
    explicit IMovement(QObject *parent = nullptr) : QObject(parent) {}

    virtual void move(Vector vector) = 0;
    virtual void stop() = 0;
};
