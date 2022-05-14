/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#include <controller.h>

#include <opencv2/imgcodecs.hpp>

#include <common.h>

using namespace std;

Controller::Controller(const QHostAddress &host, QObject *parent)
    : QObject{parent}
{
    connect(&m_commander, &ICommander::connected, this, [this, host] {
        qDebug() << "Commander connected to" << host << ":" << CONTROL_PORT;
    });

    connect(&m_commander, &ICommander::disconnected, this, [this, host] {
        qDebug() << "Commander distconnected";
        m_commander.connectToHost(host, CONTROL_PORT);
    });

    connect(&m_commander, &ICommander::errorOccurred, this, [this, host] {
        qDebug() << "Error occurred:" << m_commander.errorString();
    });


    connect(&m_receiver, &IImageReceiver::receivedFrame, this, [this](FramePtr frame) {
        QImage image(SCALED_IMAGE_WIDTH, SCALED_IMAGE_HEIGHT, QImage::Format_BGR888);
        for (int i = 0; i < frame->image.rows; ++i) {
            memcpy(image.scanLine(i),
                   frame->image.row(i).data,
                   frame->image.cols * frame->image.elemSize());
        }
        m_preview->setNewImage(image);
    });


    m_commander.connectToHost(host, CONTROL_PORT);
    qDebug() << "Commander trying to connect to " << host << ":" << CONTROL_PORT;
    m_receiver.start(FRAME_PORT);
}

Controller::~Controller()
{
    m_commander.disconnectFromHost();
    m_receiver.stop();
}

void Controller::setStreamPreview(StreamPreview *preview)
{
    m_preview = preview;
}
