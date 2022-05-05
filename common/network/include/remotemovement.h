/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#pragma once

#include <QUdpSocket>
#include <QHostAddress>

#include <imovement.h>

class RemoteMovement : public QObject, public IMovement
{
public:
    RemoteMovement(const QHostAddress &host);
    virtual ~RemoteMovement() override;

    virtual void move(Vector vector) override;
    virtual void stop() override;

private:
    QUdpSocket m_socket;
    quint64 m_sequence = 0;
};
