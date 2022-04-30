/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <picamera.h>
#include <imageprocessor.h>
#include <imagesender.h>

using namespace std;

constexpr auto IP = "192.168.100.180";

int main(int argc, char *argv[])
{
    qRegisterMetaType<FramePtr>("FramePtr");

    QCoreApplication a(argc, argv);

    auto camera = make_shared<PICamera>();
    auto processor = make_shared<ImageProcessor>(camera);
    ImageSender sender(processor, QHostAddress{IP});

    camera->start();
    processor->start();
    sender.start();

    return a.exec();
}
