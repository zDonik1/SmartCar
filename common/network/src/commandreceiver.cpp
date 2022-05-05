/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <commandreceiver.h>

using namespace std;

CommandReceiver::CommandReceiver(uint16_t port, QObject *parent)
    : ICommandReceiver(parent), m_port(port)
{}

void CommandReceiver::start()
{
    if (m_running)
        return;

    connect(&m_server, &QTcpServer::newConnection, this, &CommandReceiver::onNewConnection);
    m_server.listen(QHostAddress::AnyIPv4, m_port);
    m_running = true;
}

void CommandReceiver::stop()
{
    if (!m_running)
        return;

    disconnect(&m_server, &QTcpServer::newConnection, this, &CommandReceiver::onNewConnection);
    m_socket->disconnectFromHost();
    m_running = false;
}

QHostAddress CommandReceiver::host() const
{
    return m_socket ? m_socket->peerAddress() : QHostAddress{};
}

void CommandReceiver::onNewConnection()
{
    if (m_socket || !m_running)
        return;

    m_socket = make_unique<QTcpSocket>(m_server.nextPendingConnection());

    connect(m_socket.get(), &QAbstractSocket::disconnected, this, [this] {
        m_socket.reset();
        m_server.listen(QHostAddress::AnyIPv4, m_port);
        emit disconnected();
    });

    emit connected();
}
