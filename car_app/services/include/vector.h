/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 07/03/2022
 *
 *************************************************************************/

#pragma once


struct Vector
{
    float x;
    float y;
};

bool operator!=(const Vector &v1, const Vector &v2)
{
    return v1.x != v2.x || v1.y != v2.y;
}
