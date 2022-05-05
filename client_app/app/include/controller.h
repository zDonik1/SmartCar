/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#pragma once

#include <streampreview.h>
#include <commander.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(const QHostAddress &host, QObject *parent = nullptr);
    virtual ~Controller() override;

    Q_INVOKABLE void setStreamPreview(StreamPreview *preview);
    Q_INVOKABLE void onKeyPressed(Qt::Key key);
    Q_INVOKABLE void onKeyReleased(Qt::Key key);

private:
    StreamPreview *m_preview = nullptr;
    Commander m_commander;
};
