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
    RMoveController(QHostAddress host,
                    std::unique_ptr<IMovement> movement,
                    QObject *parent = nullptr);
    virtual ~RMoveController() override;

    bool start();
    void stop();

private slots:
    void readMoveData();

private:
    QHostAddress m_host;
    std::unique_ptr<IMovement> m_movement;
    QUdpSocket m_socket;
    bool m_running = false;
    quint64 m_lastSequence = 0;
};
