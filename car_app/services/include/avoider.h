/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#pragma once

#include <iavoider.h>

class Avoider : public IAvoider
{
public:
    Avoider(QObject *parent = nullptr);

    const Vector &vector() const override final;
    bool isBlocked() const override final;

protected:
    void setVector(Vector vector);
    void setIsBlocked(bool isBlocked);

protected:
    Vector m_vector;
    bool m_isBlocked = false;
};
