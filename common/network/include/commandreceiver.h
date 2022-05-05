/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <QTcpServer>
#include <QTcpSocket>

#include <icommandreceiver.h>

class CommandReceiver : public ICommandReceiver
{
public:
    explicit CommandReceiver(uint16_t port, QObject *parent = nullptr);

    virtual QHostAddress host() const override;

private:
    QTcpServer m_server;
    std::unique_ptr<QTcpSocket> m_socket;
};
