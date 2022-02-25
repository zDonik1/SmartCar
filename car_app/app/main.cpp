/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <picamera.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PICamera camera;
    camera.start();

    return a.exec();
}
