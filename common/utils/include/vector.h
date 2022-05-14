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
    float x = 0;
    float y = 0;

    inline auto length() const { return std::sqrt(x * x + y * y); }
    inline auto angle() const { return std::atan2(x, y) * 180 / M_PI; }
    inline auto isZero() const { return x == 0.f && y == 0.f; }
    inline auto compare(float x, float y) const { return this->x == x && this->y == y; }

    void normalize()
    {
        const auto len = length();
        x /= len;
        y /= len;
    }

    void clampLengthToOne()
    {
        if (x * x + y * y > 1) {
            normalize();
        }
    }

    bool operator==(const Vector &other) const { return compare(other.x, other.y); }

    bool operator!=(const Vector &other) const { return !(*this == other); }

    Vector operator*(float m) const { return {x * m, y * m}; }

    Vector &operator*=(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
};
