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

constexpr auto INPUT_UPDATE_RATE = 50; // ms

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    connect(&m_timer, &QTimer::timeout, this, [this] { m_movement->move(m_vector); });
}

void Controller::setStreamPreview(StreamPreview *preview)
{
    m_preview = preview;
}

void Controller::onKeyPressed(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Up:
        m_vector.y = 1;
        break;
    case Qt::Key_Down:
        m_vector.y = -1;
        break;
    case Qt::Key_Right:
        m_vector.x = 1;
        break;
    case Qt::Key_Left:
        m_vector.x = -1;
        break;
    default:;
    }
}

void Controller::onKeyReleased(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_vector.y = 0;
        break;
    case Qt::Key_Right:
    case Qt::Key_Left:
        m_vector.x = 0;
        break;
    default:;
    }
}
