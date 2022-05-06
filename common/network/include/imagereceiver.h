/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QElapsedTimer>

#include <iimagereceiver.h>

class ImageReceiver : public IImageReceiver
{
public:
    explicit ImageReceiver(QObject *parent = nullptr);
    virtual ~ImageReceiver() override;

    virtual bool start(uint16_t port) override;
    virtual void stop() override;

    virtual const QHostAddress &host() const override;

private slots:
    void readFrames();

private:
    QUdpSocket m_socket;
    QHostAddress m_host;
    cv::Mat m_mat;
    QElapsedTimer m_timer;
    bool m_running = false;
    uint64_t m_sequence = 0;
    uint64_t m_bytesRead = 0;
};
