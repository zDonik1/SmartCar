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
    enum class LookDirection { Left, Right };

public:
    explicit IMovement(QObject *parent = nullptr) : QObject(parent) {}

    virtual void move(MoveDirection direction) = 0;
    virtual void look(LookDirection direction) = 0;
    virtual void stop() = 0;

signals:
    void lookOpFinished();
};
