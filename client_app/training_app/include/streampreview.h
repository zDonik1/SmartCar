/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#pragma once

#include <QQuickPaintedItem>
#include <QPixmap>

class StreamPreview : public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit StreamPreview(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    void setNewImage(QImage image);

private:
    QImage m_image;
};
