/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#pragma once

#include <QUdpSocket>
#include <QHostAddress>

#include <vector.h>

class RemoteMovement : public QObject
{
public:
    RemoteMovement();
    virtual ~RemoteMovement() override;

    void start(const QHostAddress &host);
    void stop();

    void move(Vector vector);

private:
    QUdpSocket m_socket;
    bool m_running = false;
    quint64 m_sequence = 0;
};
