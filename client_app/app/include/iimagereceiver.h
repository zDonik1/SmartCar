/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 03/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QHostAddress>

#include <vector.h>

class IImageReceiver : public QObject
{
    Q_OBJECT

public:
    explicit IImageReceiver(QObject *parent = nullptr) : QObject(parent) {}

    virtual bool start() = 0;
    virtual void stop() = 0;

    virtual const QHostAddress &host() const = 0;

signals:
    void receivedFrame(QImage frame);
    void hostChanged();
};
