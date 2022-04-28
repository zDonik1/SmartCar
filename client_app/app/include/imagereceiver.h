/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <frame.h>

class ImageReceiver : public QObject
{
    Q_OBJECT

public:
    explicit ImageReceiver(QObject *parent = nullptr);

    void start();

signals:
    void receivedFrame(Frame frame);

private slots:
    void readFrames();

private:
    void listenToConnections();

private:
    QTcpServer m_server;
    QTcpSocket *m_socket = nullptr;
    unsigned int m_sequence = 0;
};
