/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QHostAddress>

class ICommander : public QObject
{
    Q_OBJECT

public:
    explicit ICommander(QObject *parent = nullptr) : QObject(parent) {}

    virtual void connectToHost(const QHostAddress &host, uint16_t port) = 0;
    virtual void disconnectFromHost() = 0;

    virtual QString errorString() = 0;

signals:
    void connected();
    void disconnected();
    void errorOccurred();
};
