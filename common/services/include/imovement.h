/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <vector.h>

class IMovement
{
public:
    virtual void move(Vector vector) = 0;
    virtual void stop() = 0;
};
