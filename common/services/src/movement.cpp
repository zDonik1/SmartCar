/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#include <movement.h>

#include <cmath>

#include <QTimer>

using namespace std;

inline auto invLerp(float from, float to, float value)
{
    return (value - from) / (to - from);
}

inline auto lerp(float a, float b, float w)
{
    return a + w * (b - a);
}

inline auto remap(float origFrom, float origTo, float targetFrom, float targetTo, float value)
{
    float rel = invLerp(origFrom, origTo, value);
    return lerp(targetFrom, targetTo, rel);
}

/**
 * If we start turning from 0 degress anticlockwise
 * I Quadrant = 1.0
 * II Quadrant = 1.0 -> 0.0 -> -1.0
 * III Quadrant = -1.0
 * IV Quadrant = -1.0 -> 0.0 -> 1
 */
inline auto leftMotorRatioForVector(Vector vector)
{
    const auto angle = vector.angle();
    if (angle > -180 && angle <= -90) {
        return -1.f;
    } else if (angle <= 0) {
        return remap(-90, 0, -1, 1, angle);
    } else if (angle <= 90) {
        return 1.f;
    } else if (angle <= 180) {
        return remap(90, 180, 1, -1, angle);
    } else {
        return -1.f;
    }
}


Movement::Movement(unique_ptr<IMotorActuator> leftMotor, unique_ptr<IMotorActuator> rightMotor)
    : m_leftMotor(std::move(leftMotor)), m_rightMotor(std::move(rightMotor))
{}

void Movement::move(Vector vector)
{
    if (vector.isZero()) {
        stop();
        return;
    }

    auto speed = std::clamp(vector.length(), 0.f, 1.f);
    m_leftMotor->setValue(leftMotorRatioForVector(vector) * speed);
    m_rightMotor->setValue(leftMotorRatioForVector({-vector.x, vector.y}) * speed);
}

void Movement::stop()
{
    m_leftMotor->setValue(0);
    m_rightMotor->setValue(0);
}
