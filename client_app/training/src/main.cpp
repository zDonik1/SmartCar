/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include <remotemovement.h>
#include <controller.h>

using namespace std;

constexpr auto INPUT_UPDATE_INTERVAL = 50; // ms
constexpr auto IP = "192.168.100.104";

int main(int argc, char *argv[])
{
    qmlRegisterUncreatableType<Controller>("Controller",
                                           1,
                                           0,
                                           "Controller",
                                           "Created by the main code");

    QGuiApplication app(argc, argv);

    Controller controller(make_shared<RemoteMovement>(QHostAddress{IP}), INPUT_UPDATE_INTERVAL);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");  // Import modules (assets, etc)
    engine.rootContext()->setContextProperty("controller", &controller);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    controller.start();

    return app.exec();
}
