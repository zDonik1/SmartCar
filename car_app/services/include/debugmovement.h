/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 14/03/2022
 *
 *************************************************************************/

#pragma once

#include <imovement.h>

class DebugMovement : public IMovement
{
public:
    virtual void move(Vector vector) override;
    virtual void stop() override;
};
