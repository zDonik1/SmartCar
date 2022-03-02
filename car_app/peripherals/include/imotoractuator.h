/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 25/02/2022
 *
 *************************************************************************/

#pragma once

class IMotorActuator
{
public:
    enum class Direction {
        Forward,
        Backward,
        Still,
    };

public:
    virtual void setDirection(Direction direction) = 0;
    virtual void setSpeed(float speed) = 0;
};
