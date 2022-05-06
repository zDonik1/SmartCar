/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#include <rmovecontroller.h>

#include <QNetworkDatagram>
#include <QDataStream>

#include <common.h>

RMoveController::RMoveController(std::shared_ptr<IMovement> movement, QObject *parent)
    : QObject(parent), m_movement(movement)
{
    connect(&m_socket, &QAbstractSocket::readyRead, this, &RMoveController::readMoveData);

    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this](auto state) {
        qDebug() << "Socket state changed:" << state;
    });
}

RMoveController::~RMoveController()
{
    stop();
}

bool RMoveController::start()
{
    if (m_running)
        return false;

    if (m_socket.bind(MOVE_PORT)) {
        qDebug() << "Socket bound to port" << MOVE_PORT;
        m_running = true;
        return true;
    } else {
        qWarning() << "Couldn't bind to port" << MOVE_PORT;
        return false;
    }
}

void RMoveController::stop()
{
    if (!m_running)
        return;

    m_socket.disconnectFromHost();
    m_running = false;
}

const Vector &RMoveController::vector()
{
    return m_vector;
}

void RMoveController::readMoveData()
{
    auto datagram = m_socket.receiveDatagram();
    if (datagram.isNull())
        return;

    auto buffer = datagram.data();
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    quint64 sequence;
    stream >> m_vector.x >> m_vector.y >> sequence;
    if (sequence > m_lastSequence) {
        m_movement->move(m_vector);
        m_lastSequence = sequence;
    }
}
