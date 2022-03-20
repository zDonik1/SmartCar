/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 11/03/2022
 *
 *************************************************************************/

#include <timeline.h>

#include <QTimer>

Timeline::Timeline(QObject *parent) : QObject(parent) {}

void Timeline::addCallback(int msec, std::function<void()> functor)
{
    m_callbacks.push_back({msec, functor});
}

void Timeline::start()
{
    int totalMsec = 0;
    for (auto &callback : m_callbacks) {
        totalMsec += callback.first;
        QTimer::singleShot(totalMsec, this, callback.second);
    }
    QTimer::singleShot(totalMsec, this, [this] { emit finished(); });
}
