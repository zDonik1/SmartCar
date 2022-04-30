/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#pragma once

#include <streampreview.h>
#include <imagereceiver.h>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    Q_INVOKABLE void setStreamPreview(StreamPreview *preview);

private:
    StreamPreview *m_preview = nullptr;
    ImageReceiver m_receiver;
};
