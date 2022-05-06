/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QHostAddress>

class ICommandReceiver : public QObject
{
    Q_OBJECT

public:
    explicit ICommandReceiver(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual QHostAddress host() const = 0;

signals:
    void connected();
    void disconnected();
};
