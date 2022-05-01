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

void ImageProcessor::start(std::shared_ptr<ICamera> camera)
{
    if (m_processThread.isRunning())
        return;

    m_camera = camera;
    connect(m_camera.get(), &ICamera::frameReady, this, [this](auto frame) {
        m_processThread.enqueueFrame(frame);
    });

    m_processThread.start();
}

void ImageProcessor::stop()
{
    m_camera.reset();
    m_processThread.stop();
}
