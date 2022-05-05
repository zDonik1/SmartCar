/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#include <remotemovement.h>

#include <QDataStream>

#include <common.h>

RemoteMovement::RemoteMovement(const QHostAddress &host)
{
    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this](auto state) {
        qDebug() << "Socket state changed:" << state;
    });

    m_socket.connectToHost(host, MOVE_PORT);
}

RemoteMovement::~RemoteMovement()
{
    m_socket.disconnectFromHost();
}

void RemoteMovement::stop()
{
    move({0, 0});
}

void RemoteMovement::move(Vector vector)
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << vector.x << vector.y << m_sequence++;
    if (m_socket.write(buffer) < 0) {
        qDebug() << "Failed to send move vector:" << m_socket.errorString();
    }
}
