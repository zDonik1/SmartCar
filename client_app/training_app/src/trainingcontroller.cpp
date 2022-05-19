/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <trainingcontroller.h>

using namespace std;

TrainingController::TrainingController(shared_ptr<IMovement> movement, int tickInterval, QObject *parent)
    : QObject(parent), m_movement(movement), m_tickInterval(tickInterval)
{
    connect(&m_timer, &QTimer::timeout, this, [this] { m_movement->move(m_vector); });
}

TrainingController::~TrainingController()
{
    stop();
}

void TrainingController::start()
{
    m_timer.start(m_tickInterval);
}

void TrainingController::stop()
{
    m_timer.stop();
}

void TrainingController::setStreamPreview(StreamPreview *preview)
{
}

void TrainingController::onKeyPressed(Qt::Key key)
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

void TrainingController::onKeyReleased(Qt::Key key)
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
