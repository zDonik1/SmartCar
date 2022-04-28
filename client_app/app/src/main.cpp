/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <imagereceiver.h>

using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Frame>("Frame");

    QCoreApplication a(argc, argv);

    ImageReceiver receiver;
    receiver.start();

    QObject::connect(&receiver, &ImageReceiver::receivedFrame, &a, [](Frame frame) {
        qDebug() << "received frame" << frame.sequence;
    });

    return a.exec();
}
