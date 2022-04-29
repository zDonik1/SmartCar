/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 28/04/2022
 *
 *************************************************************************/

#include <streampreview.h>

#include <QPainter>

StreamPreview::StreamPreview(QQuickItem *parent) : QQuickPaintedItem(parent) {}

void StreamPreview::paint(QPainter *painter)
{
    painter->drawImage(QRectF(QPointF{}, size()), m_image);
}

void StreamPreview::setNewImage(QImage image)
{
    m_image = image;
    update();
}
