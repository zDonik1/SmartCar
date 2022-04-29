/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#include <controller.h>

#include <common.h>
#include <opencv2/imgcodecs.hpp>

Controller::Controller(QObject *parent) : QObject{parent}
{
    connect(&m_receiver, &ImageReceiver::receivedFrame, this, [this](QImage frame) {
        if (m_preview) {
            m_preview->setNewImage(frame);
        }
    });

    m_receiver.start();
}

void Controller::setStreamPreview(StreamPreview *preview)
{
    m_preview = preview;
}
