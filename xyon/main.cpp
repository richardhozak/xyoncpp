#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "xyoncontroller.h"

#include <QQuickView>
#include <QWindow>
#include "xyonwindow.h"
#include "audioentry.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<QObjectListModel*>("QObjectListModel*");
    qRegisterMetaType<XyonPlaylist*>("XyonPlaylist*");
    //qRegisterMetaType<AudioEntry*>("AudioEntry*");

    QQmlApplicationEngine engine;
    XyonController *controller = new XyonController(engine.rootContext());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Q_UNUSED(controller)

//    XyonWindow *window = new XyonWindow();

//    QQuickView *view = new QQuickView(window);

//    XyonController *controller = new XyonController(view->rootContext());

//    view->setResizeMode(QQuickView::SizeRootObjectToView);
//    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    view->show();

//    qDebug() << "Hello" << view->parent();


    return app.exec();
}
