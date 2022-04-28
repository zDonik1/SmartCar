/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <queue>

#include <QThread>

#include <icamera.h>

class ImageProcessor : public QThread
{
    Q_OBJECT

public:
    explicit ImageProcessor(std::shared_ptr<ICamera> camera, QObject *parent = nullptr);

Q_SIGNALS:
    void frameReady(FramePtr frame);

private:
    void run() override;

private:
    std::shared_ptr<ICamera> m_camera;
    std::queue<FramePtr> m_frameRefs;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};
