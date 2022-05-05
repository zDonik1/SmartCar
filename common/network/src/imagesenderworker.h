/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#pragma once

#include <mutex>

#include <QObject>
#include <QUdpSocket>

#include <frame.h>

using namespace std;

class ImageSenderWorker : public QObject
{
    Q_OBJECT

public:
    explicit ImageSenderWorker(const QHostAddress &host, uint16_t port, QObject *parent = nullptr);

    void start();
    void stop();

signals:
    void sendFrame(FramePtr frame);

private slots:
    void onSendFrame(FramePtr frame);

private:
    QHostAddress m_host;
    uint16_t m_port;
    QUdpSocket m_socket;
    atomic_bool m_running = false;
    mutex m_mutex;
};
