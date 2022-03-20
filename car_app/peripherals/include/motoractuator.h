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

    virtual void setValue(float value) override;

private:
    void updateMotors();

private:
    static constexpr int MIN_SPEED = 0;
    static constexpr int MAX_SPEED = 100;

    int m_forwardPinN = -1;
    int m_backwardPinN = -1;
};
