/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <commander.h>

Commander::Commander(QObject *parent) : ICommander(parent)
{
    connect(&m_socket, &QAbstractSocket::connected, this, &ICommander::connected);
    connect(&m_socket, &QAbstractSocket::disconnected, this, &ICommander::disconnected);
    connect(&m_socket, &QAbstractSocket::errorOccurred, this, &ICommander::errorOccurred);
}

void Commander::connectToHost(const QHostAddress &host, uint16_t port)
{
    m_socket.connectToHost(host, port);
}

void Commander::disconnectFromHost()
{
    m_socket.disconnectFromHost();
}

QString Commander::errorString()
{
    return m_socket.errorString();
}
