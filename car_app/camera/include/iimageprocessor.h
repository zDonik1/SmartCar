/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 01/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <icamera.h>

class IImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit IImageProcessor(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;

public Q_SLOTS:
    virtual void processFrame(FramePtr frame) = 0;

Q_SIGNALS:
    void frameReady(FramePtr frame);
};
