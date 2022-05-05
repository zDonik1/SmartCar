/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#pragma once

#include <QTimer>

#include <streampreview.h>
#include <imagereceiver.h>
#include <remotemovement.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);

    Q_INVOKABLE void setStreamPreview(StreamPreview *preview);
    Q_INVOKABLE void onKeyPressed(Qt::Key key);
    Q_INVOKABLE void onKeyReleased(Qt::Key key);

private:
    Vector vectorFromKeyboard();

private:
    StreamPreview *m_preview = nullptr;
    std::unique_ptr<RemoteMovement> m_movement;
    QTimer m_timer;
    Vector m_vector;
};
