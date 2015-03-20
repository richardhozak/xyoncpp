#include "xyoncontroller.h"
#include "audioentry.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

XyonController::XyonController(QQmlContext *context, QObject *parent) : QObject(parent)
{
    player = new QMediaPlayer(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost", 2323);
    connect(socket, &QTcpSocket::readyRead, this, &XyonController::receive);
    searchList = new QObjectListModel(this);

    context->setContextProperty("controller", this);
    context->setContextProperty("searchList", searchList);
    context->setContextProperty("mediaPlayer", player);

    player->setNotifyInterval(50);
//    player->setMedia(QUrl::fromLocalFile("/home/richard/Downloads/song.wav"));
//    player->play();
}

void XyonController::playId(const QString &id)
{
    this->writeMethod("get_stream_link", id);
}

void XyonController::writeMethod(const QString &method, const QString &query)
{
    QJsonObject obj {
        {"method", method},
        {"params", query}
    };

    QByteArray arr = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    arr.push_back('\n');

    qDebug() << "Sending" << arr;

    socket->write(arr);
}

void XyonController::search(const QString &query)
{
    this->writeMethod("search", query);
}

void XyonController::receive()
{
    QJsonDocument doc = QJsonDocument::fromJson(this->socket->readAll());
    qDebug() << doc;
    if (doc.isObject())
    {
        QJsonObject rootObject = doc.object();
        if (!rootObject.contains("method") && !rootObject.contains("params"))
            return;

        if (rootObject["method"] == "response_search")
        {
            if (rootObject["params"].isArray())
            {
                searchList->clear();
                QJsonArray array = rootObject["params"].toArray();
                for (int i = 0; i < array.size(); i++)
                {
                    AudioEntry *res = AudioEntry::fromJson(array[i].toObject());
                    if (res != NULL)
                    {
                        qDebug() << "Adding:" << res->getId() << "to list.";
                        searchList->append(res);
                    }
                }
            }
        }
        else if (rootObject["method"] == "response_get_stream_link")
        {
            if (rootObject["params"].isString())
            {
                player->stop();
                QString url = rootObject["params"].toString();
                qDebug() << "Playing" << url;
                player->setMedia(QUrl(url));
                player->play();
            }
        }
    }
}

void XyonController::test()
{
    this->player->setPosition(this->player->duration() / 2);
}
