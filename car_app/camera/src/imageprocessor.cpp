/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imageprocessor.h>

#include <QDataStream>
#include <QDebug>

using namespace std;

ImageProcessor::ImageProcessor(std::shared_ptr<ICamera> camera, QObject *parent)
    : QThread(parent), m_camera(camera)
{
    connect(m_camera.get(), &ICamera::frameReady, this, [this](FramePtr frame) {
        lock_guard<mutex> lock(m_mutex);
        m_frameRefs.push(frame);
        m_condVar.notify_all();
    });
}

void ImageProcessor::run()
{
    while (true) {
        unique_lock<mutex> lock(m_mutex);
        m_condVar.wait(lock, [this] { return !m_frameRefs.empty(); });

        auto frame = m_frameRefs.front();
        m_frameRefs.pop();

        Q_EMIT frameReady(frame);
    }
}
