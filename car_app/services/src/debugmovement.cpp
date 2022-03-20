/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 14/03/2022
 *
 *************************************************************************/

#include <debugmovement.h>

#include <QDebug>

void DebugMovement::move(Vector vector)
{
    if (vector.compare(0, 0)) {
        qDebug() << "Stopped in move";
    } else if (vector.compare(0, 1)) {
        qDebug() << "Going forward";
    } else if (vector.compare(0, -1)) {
        qDebug() << "Going backward";
    } else if (vector.compare(1, 0)) {
        qDebug() << "Turning right";
    } else if (vector.compare(-1, 0)) {
        qDebug() << "Turning left";
    } else {
        qDebug() << "Move vector:" << vector.x << vector.y;
    }
}

void DebugMovement::stop()
{
    qDebug() << "Stopped in move";
}
