/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <QObject>
#include <QTimer>

#include <imovement.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(std::shared_ptr<IMovement> movement,
               int tickInterval,
               QObject *parent = nullptr);
    virtual ~Controller() override;

    void start();
    void stop();

    Q_INVOKABLE void onKeyPressed(Qt::Key key);
    Q_INVOKABLE void onKeyReleased(Qt::Key key);

private:
    std::shared_ptr<IMovement> m_movement;
    QTimer m_timer;
    Vector m_vector;
    int m_tickInterval = 50; // ms;
};
