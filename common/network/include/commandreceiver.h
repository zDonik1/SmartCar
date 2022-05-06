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

    virtual void start() override;
    virtual void stop() override;

    virtual QHostAddress host() const override;

private slots:
    void onNewConnection();

private:
    QTcpServer m_server;
    std::unique_ptr<QTcpSocket> m_socket;
    uint16_t m_port;
    bool m_running = false;
};
