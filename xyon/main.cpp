#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "xyoncontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    XyonController *controller = new XyonController(engine.rootContext());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
