/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <queue>

#include <QThread>

#include <iimageprocessor.h>

class ImageProcessor : public IImageProcessor
{
    class ProcessThread : public QThread
    {
    public:
        explicit ProcessThread(ImageProcessor *processor, QObject *parent = nullptr)
            : QThread(parent), m_processor(processor)
        {}

        void start();
        void stop();

        void enqueueFrame(FramePtr frame);

    protected:
        void run() override;

    private:
        ImageProcessor *m_processor = nullptr;
        std::queue<FramePtr> m_frameRefs;
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        bool m_stop = false;
    };

public:
    explicit ImageProcessor(QObject *parent = nullptr);
    virtual ~ImageProcessor();

    virtual void start() override;
    virtual void stop() override;

public Q_SLOTS:
    virtual void processFrame(FramePtr frame) override;

private:
    ProcessThread m_processThread;
};
