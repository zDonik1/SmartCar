/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <movement.h>

#include <QTimer>
#include <QDebug>

using namespace std;

constexpr auto MAX_SPEED = 1;


Movement::Movement(unique_ptr<IMotorActuator> leftMotor, unique_ptr<IMotorActuator> rightMotor)
    : m_leftMotor(std::move(leftMotor)), m_rightMotor(std::move(rightMotor))
{
    m_leftMotor->setSpeed(MAX_SPEED);
    m_rightMotor->setSpeed(MAX_SPEED);
}

void Movement::move(MoveDirection direction)
{
    qDebug() << "moved to" << direction;

    auto motorDirection = direction == MoveDirection::Forwad ? IMotorActuator::Direction::Forward
                                                             : IMotorActuator::Direction::Backward;
    m_leftMotor->setDirection(motorDirection);
    m_rightMotor->setDirection(motorDirection);
}

void Movement::turn(TurnDirection direction)
{
    qDebug() << "looked at" << direction;

    m_leftMotor->setDirection(direction == TurnDirection::Right
                                  ? IMotorActuator::Direction::Forward
                                  : IMotorActuator::Direction::Backward);
    m_rightMotor->setDirection(direction == TurnDirection::Right
                                   ? IMotorActuator::Direction::Backward
                                   : IMotorActuator::Direction::Forward);
}

void Movement::stop()
{
    qDebug() << __func__;

    m_leftMotor->setDirection(IMotorActuator::Direction::Still);
    m_rightMotor->setDirection(IMotorActuator::Direction::Still);
}
