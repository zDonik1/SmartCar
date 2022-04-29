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

#include <controller.h>

using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Frame>("Frame");
    qmlRegisterType<StreamPreview>("Stream", 1, 0, "StreamPreview");
    qmlRegisterUncreatableType<Controller>("Controller",
                                           1,
                                           0,
                                           "Controller",
                                           "Created by the main code");

    QGuiApplication app(argc, argv);

    Controller controller;

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

    return app.exec();
}
