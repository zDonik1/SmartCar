/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <QUdpSocket>

#include <imovement.h>

class RMoveController : public QObject
{
    Q_OBJECT

public:
    RMoveController(std::shared_ptr<IMovement> movement, uint16_t port, QObject *parent = nullptr);
    virtual ~RMoveController() override;

    bool start();
    void stop();

    const Vector &vector();

private slots:
    void readMoveData();

private:
    std::shared_ptr<IMovement> m_movement;
    QUdpSocket m_socket;
    Vector m_vector;
    uint16_t m_port;
    bool m_running = false;
    quint64 m_lastSequence = 0;
};
