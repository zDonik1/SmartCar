/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#include <avoider.h>

Avoider::Avoider(QObject *parent) : IAvoider(parent) {}


const Vector &Avoider::vector() const
{
    return m_vector;
}

bool Avoider::isBlocked() const
{
    return m_isBlocked;
}


void Avoider::setVector(Vector vector)
{
    if (m_vector != vector) {
        m_vector = vector;
        emit vectorChanged();
    }
}

void Avoider::setIsBlocked(bool isBlocked)
{
    if (m_isBlocked != isBlocked) {
        m_isBlocked = isBlocked;
        emit isBlockedChanged();
    }
}
