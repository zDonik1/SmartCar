/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <frame.h>

class ICamera : public QObject
{
    Q_OBJECT

public:
    explicit ICamera(QObject *parent = nullptr) : QObject(parent) {}

    virtual bool start() = 0;
    virtual void stop() = 0;

Q_SIGNALS:
    void frameReady(FramePtr frame);
};
