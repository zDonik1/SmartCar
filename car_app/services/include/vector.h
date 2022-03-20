/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 07/03/2022
 *
 *************************************************************************/

#pragma once

#include <cmath>


struct Vector
{
    float x;
    float y;

    inline auto length() { return std::sqrt(x * x + y * y); }
    inline auto angle() { return std::atan2(x, y) * 180 / M_PI; }
    inline auto isZero() { return x == 0.f && y == 0.f; }
    inline auto compare(float x, float y) { return this->x == x && this->y == y; }

    void normalize()
    {
        const auto len = length();
        x /= len;
        y /= len;
    }

    bool operator==(const Vector &other) { return compare(other.x, other.y); }

    bool operator!=(const Vector &other) { return !(*this == other); }
};

