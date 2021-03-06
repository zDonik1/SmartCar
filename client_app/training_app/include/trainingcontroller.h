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

#include <streampreview.h>
#include <imovement.h>

class TrainingController : public QObject
{
public:
    TrainingController(std::shared_ptr<IMovement> movement,
                       int tickInterval,
                       QObject *parent = nullptr);
    virtual ~TrainingController() override;

    void start();
    void stop();

    Q_INVOKABLE void setStreamPreview(StreamPreview *preview);
    Q_INVOKABLE void onKeyPressed(Qt::Key key);
    Q_INVOKABLE void onKeyReleased(Qt::Key key);

private:
    std::shared_ptr<IMovement> m_movement;
    QTimer m_timer;
    Vector m_vector;
    int m_tickInterval = 50; // ms;
};
