/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>
#include <QUdpSocket>

#include <imageprocessor.h>

class ImageSender : public QObject
{
    Q_OBJECT

public:
    ImageSender(std::shared_ptr<ImageProcessor> imageProcessor, QObject *parent = nullptr);

private slots:
    void sendFrame(FramePtr frame);

private:
    std::shared_ptr<ImageProcessor> m_imageProcessor;
    QUdpSocket m_socket;
};
