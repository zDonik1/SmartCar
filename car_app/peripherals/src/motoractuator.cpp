/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#include <QDebug>

#include <motoractuator.h>

#include <wiringPi.h>
#include <softPwm.h>


MotorActuator::MotorActuator(int forwardPinN, int backwardPinN)
{
    if (wiringPiSetup() < 0) {
        qWarning() << "Wiring PI was not set up!";
        return;
    }

    m_forwardPinN = forwardPinN;
    m_backwardPinN = backwardPinN;

    pinMode(m_forwardPinN, SOFT_PWM_OUTPUT);
    pinMode(m_backwardPinN, SOFT_PWM_OUTPUT);

    softPwmCreate(m_forwardPinN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(m_backwardPinN, MIN_SPEED, MAX_SPEED);
}

MotorActuator::~MotorActuator()
{
}

void MotorActuator::setDirection(Direction direction)
{
    m_direction = direction;
    updateMotors();
}

void MotorActuator::setSpeed(float speed)
{
    m_speed = speed;
    updateMotors();
}

void MotorActuator::updateMotors()
{
    switch (m_direction) {
    case Direction::Forward: {
        softPwmWrite(m_forwardPinN, MAX_SPEED * m_speed);
        softPwmWrite(m_backwardPinN, MIN_SPEED);
        break;
    }
    case Direction::Backward: {
        softPwmWrite(m_forwardPinN, MIN_SPEED);
        softPwmWrite(m_backwardPinN, MAX_SPEED * m_speed);
        break;
    }
    case Direction::Still: {
        softPwmWrite(m_forwardPinN, MIN_SPEED);
        softPwmWrite(m_backwardPinN, MIN_SPEED);
        break;
    }
    }
}
