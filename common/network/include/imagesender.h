/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>
#include <QHostAddress>

#include <iimagesender.h>

class ImageSenderWorker;

class ImageSender : public IImageSender
{
public:
    ImageSender(const QHostAddress &host, uint16_t port, QObject *parent = nullptr);
    virtual ~ImageSender() override;

    virtual void start() override;
    virtual void stop() override;

public slots:
    virtual void sendFrame(FramePtr frame) override;

private:
    std::unique_ptr<ImageSenderWorker> m_worker;
    QThread m_thread;
    bool m_running = false;
};
