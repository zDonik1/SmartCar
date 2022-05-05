/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <QTcpSocket>

#include <icommander.h>

class Commander : public ICommander
{
public:
    explicit Commander(QObject *parent = nullptr);

    virtual void connectToHost(const QHostAddress &host, uint16_t port) override;
    virtual void disconnectFromHost() override;

private:
    QTcpSocket m_socket;
};
