/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imageprocessor.h>

using namespace std;


// ==== ProcessThread ==============================================================

void ImageProcessor::ProcessThread::start()
{
    m_stop = false;
    QThread::start();
}

void ImageProcessor::ProcessThread::stop()
{
    lock_guard<mutex> lock(m_mutex);
    m_stop = true;
    m_condVar.notify_all();
}

void ImageProcessor::ProcessThread::enqueueFrame(FramePtr frame)
{
    lock_guard<mutex> lock(m_mutex);
    m_frameRefs.push(frame);
    m_condVar.notify_all();
}

void ImageProcessor::ProcessThread::run()
{
    while (true) {
        unique_lock<mutex> lock(m_mutex);
        m_condVar.wait(lock, [this] { return m_stop || !m_frameRefs.empty(); });

        if (m_stop)
            return;

        auto frame = m_frameRefs.front();
        m_frameRefs.pop();

        Q_EMIT m_processor->frameReady(frame);
    }
}


// ==== ImageProcessor ==============================================================

ImageProcessor::ImageProcessor(QObject *parent)
    : IImageProcessor(parent), m_processThread(this)
{}

ImageProcessor::~ImageProcessor()
{
    ImageProcessor::stop();
    m_processThread.wait();
}

void ImageProcessor::start()
{
    if (m_processThread.isRunning())
        return;

    m_processThread.start();
}

void ImageProcessor::stop()
{
    m_processThread.stop();
}

void ImageProcessor::processFrame(FramePtr frame)
{
    if (!m_processThread.isRunning())
        return;

    m_processThread.enqueueFrame(frame);
}
