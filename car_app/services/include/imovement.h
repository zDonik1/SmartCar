/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

class IMovement : public QObject
{
    Q_OBJECT

public:
    enum class MoveDirection { Forwad, Backward };
    Q_ENUM(MoveDirection)
    enum class TurnDirection { Left, Right };
    Q_ENUM(TurnDirection)

public:
    explicit IMovement(QObject *parent = nullptr) : QObject(parent) {}

    virtual void move(MoveDirection direction) = 0;
    virtual void turn(TurnDirection direction) = 0;
    virtual void stop() = 0;
};
