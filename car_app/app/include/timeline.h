/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 11/03/2022
 *
 *************************************************************************/

#pragma once

#include <vector>

#include <QObject>


class Timeline : public QObject
{
    Q_OBJECT

public:
    explicit Timeline(QObject *parent = nullptr);

    void addCallback(int msec, std::function<void()> functor);
    void start();

signals:
    void finished();

private:
    std::vector<std::pair<int, std::function<void()>>> m_callbacks;
};
