/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDebug>

#include <common.h>

using namespace std;

Controller::Controller(shared_ptr<IMovement> movement, int tickInterval, QObject *parent)
    : QObject(parent), m_movement(movement), m_tickInterval(tickInterval)
{
    connect(&m_timer, &QTimer::timeout, this, [this] {
        qDebug() << m_vector.x << m_vector.y;
        m_movement->move(m_vector);
    });
}

Controller::~Controller()
{
    stop();
}

void Controller::start()
{
    m_timer.start(m_tickInterval);
}

void Controller::stop()
{
    m_timer.stop();
}

void Controller::onKeyPressed(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Up:
        m_vector.y += 1;
        break;
    case Qt::Key_Down:
        m_vector.y -= 1;
        break;
    case Qt::Key_Right:
        m_vector.x += 1;
        break;
    case Qt::Key_Left:
        m_vector.x -= 1;
        break;
    default:;
    }
}

void Controller::onKeyReleased(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Up:
        m_vector.y -= 1;
        break;
    case Qt::Key_Down:
        m_vector.y += 1;
        break;
    case Qt::Key_Right:
        m_vector.x -= 1;
        break;
    case Qt::Key_Left:
        m_vector.x += 1;
        break;
    default:;
    }
}
