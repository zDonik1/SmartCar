/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 01/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <frame.h>

class IImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit IImageProcessor(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;

public slots:
    virtual void processFrame(FramePtr frame) = 0;

signals:
    void frameReady(FramePtr frame);
};
