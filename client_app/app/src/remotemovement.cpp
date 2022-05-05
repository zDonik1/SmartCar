/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#include <remotemovement.h>

#include <QDataStream>

#include <common.h>

RemoteMovement::RemoteMovement()
{
    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this](auto state) {
        qDebug() << "Socket state changed:" << state;
    });
}

RemoteMovement::~RemoteMovement()
{
    stop();
}

void RemoteMovement::start(const QHostAddress &host)
{
    if (m_running)
        return;

    m_socket.connectToHost(host, MOVE_PORT);
    m_running = true;
}

void RemoteMovement::stop()
{
    if (!m_running)
        return;

    m_socket.disconnectFromHost();
    m_running = false;
}

void RemoteMovement::move(Vector vector)
{
    if (!m_running)
        return;

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << vector.x << vector.y << m_sequence++;
    if (m_socket.write(buffer) < 0) {
        qDebug() << "Failed to send move vector:" << m_socket.errorString();
    }
}
