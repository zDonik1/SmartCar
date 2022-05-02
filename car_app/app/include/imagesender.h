/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QUdpSocket>

#include <iimagesender.h>

class ImageSender : public IImageSender
{
public:
    ImageSender(QHostAddress address,
                QObject *parent = nullptr);
    virtual ~ImageSender();

    virtual void start() override;
    virtual void stop() override;

public slots:
    virtual void sendFrame(FramePtr frame) override;

private:
    QHostAddress m_address;
    QUdpSocket m_socket;
    bool m_running = false;
};
