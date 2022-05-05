/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 03/05/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <frame.h>

class IImageSender : public QObject
{
public:
    explicit IImageSender(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;

public slots:
    virtual void sendFrame(FramePtr frame) = 0;
};
