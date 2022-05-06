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

    connect(&m_commander, &ICommander::disconnected, this, [this] {
        qDebug() << "Commander distconnected";
    });

    m_commander.connectToHost(host, CONTROL_PORT);
    qDebug() << "Commander trying to connect to " << host << ":" << CONTROL_PORT;
}

Controller::~Controller()
{
    m_commander.disconnectFromHost();
}

void Controller::setStreamPreview(StreamPreview *preview)
{
    m_preview = preview;
}

void Controller::onKeyPressed(Qt::Key key)
{
}

void Controller::onKeyReleased(Qt::Key key)
{
}
