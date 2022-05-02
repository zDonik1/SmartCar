/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <lccamera.h>
#include <imageprocessor.h>
#include <imagesender.h>

using namespace std;

constexpr auto IP = "192.168.100.180";
constexpr auto DEFAULT_CAMERA = 0;
constexpr unsigned int CAPTURE_HEIGHT = 480;
constexpr unsigned int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;

int main(int argc, char *argv[])
{
    qRegisterMetaType<FramePtr>("FramePtr");

    QCoreApplication a(argc, argv);

    auto camera = make_shared<LCCamera>(DEFAULT_CAMERA, CAPTURE_HEIGHT, CAPTURE_WIDTH);
    auto processor = make_shared<ImageProcessor>();
    ImageSender sender(processor, QHostAddress{IP});

    camera->start();
    processor->start(camera);
    sender.start();

    return a.exec();
}
