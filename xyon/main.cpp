#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>
#include "xyoncontroller.h"

#include <QQuickView>
#include <QWindow>
#include "audioentry.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<QObjectListModel*>("QObjectListModel*");
    qRegisterMetaType<XyonPlaylist*>("XyonPlaylist*");

    QQmlApplicationEngine engine;
    XyonController *controller = new XyonController(engine.rootContext());
    controller->initializeController();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Q_UNUSED(controller)

    return app.exec();
}
