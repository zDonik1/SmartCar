/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include <motoractuator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MotorActuator leftMotors(1, 4);
    MotorActuator rightMotors(5, 6);
    leftMotors.setSpeed(1.0);
    rightMotors.setSpeed(1.0);

    leftMotors.setDirection(MotorActuator::Direction::Forward);
    rightMotors.setDirection(MotorActuator::Direction::Forward);
    QThread::sleep(1);

    leftMotors.setDirection(MotorActuator::Direction::Backward);
    rightMotors.setDirection(MotorActuator::Direction::Backward);
    QThread::sleep(1);

    leftMotors.setDirection(MotorActuator::Direction::Still);
    rightMotors.setDirection(MotorActuator::Direction::Still);

    return a.exec();
}
