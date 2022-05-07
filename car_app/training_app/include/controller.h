/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <QThread>

#include <icamera.h>
#include <rmovecontroller.h>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(RMoveController *moveController);

public slots:
    void writeFrame(FramePtr frame);

private:
    RMoveController *m_moveController = nullptr;
};

class Controller : public QObject
{
public:
    Controller(std::shared_ptr<ICamera> camera,
               std::shared_ptr<IMovement> movement,
               QObject *parent = nullptr);
    virtual ~Controller() override;

    void start();
    void stop();

private:
    std::shared_ptr<ICamera> m_camera;
    RMoveController m_moveController;
    Worker m_worker;
    QThread m_thread;
};
