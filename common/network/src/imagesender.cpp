/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imagesender.h>

#include <imagesenderworker.h>

ImageSender::ImageSender(QHostAddress host, QObject *parent)
    : IImageSender(parent), m_worker(make_unique<ImageSenderWorker>(host))
{
    m_worker->moveToThread(&m_thread);
}

ImageSender::~ImageSender()
{
    ImageSender::stop();
}

void ImageSender::start()
{
    if (m_running)
        return;

    m_thread.start();
    m_worker->start();
    m_running = true;
}

void ImageSender::stop()
{
    if (!m_running)
        return;

    m_worker->stop();
    m_thread.quit();
    m_thread.wait();
    m_running = false;
}

void ImageSender::sendFrame(FramePtr frame)
{
    if (!m_running)
        return;

    emit m_worker->sendFrame(frame);
}
