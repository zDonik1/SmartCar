/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#pragma once

#include <imotoractuator.h>

class MotorActuator : public IMotorActuator
{
public:
    MotorActuator(int forwardPinN, int backwardPinN);
    virtual ~MotorActuator();

    virtual void setDirection(Direction direction) override;
    virtual void setSpeed(float speed) override;

private:
    void updateMotors();

private:
    static constexpr int MIN_SPEED = 0;
    static constexpr int MAX_SPEED = 100;

    int m_forwardPinN = -1;
    int m_backwardPinN = -1;
    Direction m_direction = Direction::Still;
    float m_speed = MIN_SPEED;
};
