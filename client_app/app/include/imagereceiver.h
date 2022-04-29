/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QUdpSocket>
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
    QUdpSocket m_socket;
    QImage m_image;
    QElapsedTimer m_timer;
    uint64_t m_sequence = 0;
    uint64_t m_bytesRead = 0;
};
