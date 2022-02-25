/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QDebug>

#include <opencv2/videoio.hpp>

#include <picamera.h>

PICamera::PICamera()
{
    qDebug() << m_capture->open("/dev/video0");
}

PICamera::~PICamera()
{
}

FramePtr PICamera::newFrame() const
{
}
