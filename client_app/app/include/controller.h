/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#pragma once

#include <streampreview.h>
#include <commander.h>
#include <imagereceiver.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(const QHostAddress &host, QObject *parent = nullptr);
    virtual ~Controller() override;

    Q_INVOKABLE void setStreamPreview(StreamPreview *preview);

private:
    StreamPreview *m_preview = nullptr;
    Commander m_commander;
    ImageReceiver m_receiver;
};
