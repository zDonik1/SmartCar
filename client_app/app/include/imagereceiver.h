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
#include <QImage>
#include <QElapsedTimer>

#include <frame.h>

class ImageReceiver : public QObject
{
    Q_OBJECT

public:
    explicit ImageReceiver(QObject *parent = nullptr);

    void start();

signals:
    void receivedFrame(QImage frame);

private slots:
    void readFrames();

private:
    void listenToConnections();

private:
    QTcpServer m_server;
    QTcpSocket *m_socket = nullptr;
    QImage m_image;
    QElapsedTimer m_timer;
    int m_row = 0;
    uint64_t m_bytesRead = 0;
};
