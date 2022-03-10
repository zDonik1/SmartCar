/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <imovement.h>
#include <imotoractuator.h>


class Movement : public IMovement
{
    Q_OBJECT

public:
    Movement(std::unique_ptr<IMotorActuator> leftMotor, std::unique_ptr<IMotorActuator> rightMotor);

    virtual void move(Vector vector) override;
    virtual void stop() override;

private:
    std::unique_ptr<IMotorActuator> m_leftMotor;
    std::unique_ptr<IMotorActuator> m_rightMotor;
};
