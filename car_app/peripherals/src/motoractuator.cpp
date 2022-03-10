/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#include <motoractuator.h>

#include <QDebug>

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

MotorActuator::~MotorActuator() {}

void MotorActuator::setValue(float value)
{
    value = std::clamp(value, -1.f, 1.f);
    const auto speed = MAX_SPEED * std::abs(value);
    softPwmWrite(m_forwardPinN, value > 0 ? speed : MIN_SPEED);
    softPwmWrite(m_backwardPinN, value < 0 ? speed : MIN_SPEED);
}
