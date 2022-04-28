/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <imagereceiver.h>

using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Frame>("Frame");

    QGuiApplication app(argc, argv);

    ImageReceiver receiver;
    receiver.start();

    QObject::connect(&receiver, &ImageReceiver::receivedFrame, &app, [](Frame frame) {
        qDebug() << "received frame" << frame.sequence;
    });

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");  // Import modules (assets, etc)
    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
