/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <commandreceiver.h>

using namespace std;

CommandReceiver::CommandReceiver(uint16_t port, QObject *parent) : ICommandReceiver(parent)
{
    connect(&m_server, &QTcpServer::newConnection, this, [this, port] {
        if (m_socket)
            return;

        m_socket = make_unique<QTcpSocket>(m_server.nextPendingConnection());

        connect(m_socket.get(), &QAbstractSocket::disconnected, this, [this, port] {
            m_socket.reset();
            m_server.listen(QHostAddress::AnyIPv4, port);
            emit disconnected();
        });

        emit connected();
    });

    m_server.listen(QHostAddress::AnyIPv4, port);
}

QHostAddress CommandReceiver::host() const
{
    return m_socket ? m_socket->peerAddress() : QHostAddress{};
}
