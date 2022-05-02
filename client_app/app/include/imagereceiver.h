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

#include <iimagereceiver.h>

class ImageReceiver : public IImageReceiver
{
public:
    explicit ImageReceiver(QObject *parent = nullptr);

    virtual bool start() override;
    virtual void stop() override;

private slots:
    void readFrames();

private:
    QUdpSocket m_socket;
    QImage m_image;
    QElapsedTimer m_timer;
    uint64_t m_sequence = 0;
    uint64_t m_bytesRead = 0;
};
