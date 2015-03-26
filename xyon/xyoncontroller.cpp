#include "xyoncontroller.h"
#include "audioentry.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>

XyonController::XyonController(QQmlContext *context, QObject *parent) : QObject(parent), page(1)
{
    entry = NULL;

    player = new QMediaPlayer(this);
    playlist = new XyonPlaylist(player);

    this->process = NULL;
    socket = new QTcpSocket(this);
    searchList = new QObjectListModel(this);

    context->setContextProperty("controller", this);
    context->setContextProperty("searchList", searchList);
    context->setContextProperty("mediaPlayer", player);

    player->setNotifyInterval(200);


    connect(socket, &QTcpSocket::readyRead, this, &XyonController::receive);
    connect(playlist, &XyonPlaylist::resolveUrl, this, &XyonController::resolveUrl);


    //this->connectToHost();
//    player->setMedia(QUrl::fromLocalFile("/home/richard/Downloads/song.wav"));
//    player->play();
}

bool XyonController::initializeController()
{
//#ifndef QT_DEBUG

//    QDir dir(QDir::currentPath());
//    QString xyonServerExecutable = dir.entryList(QStringList("xyon-server*"), QDir::Executable | QDir::Files).first();
//    QString executablePath = dir.path() + "/" + xyonServerExecutable;
//    //qDebug() << executablePath;

//    this->process = new QProcess(this);
//    this->process->start(executablePath);
//    //process->waitForStarted();
//    this->process->waitForReadyRead(2000);

//    qDebug() << this->process->pid();

//    QString read = this->process->readAllStandardOutput().simplified();

//    qDebug() << read;

//    if (read == "ERROR")
//    {
//        return false;
//    }

//    this->process->setProcessChannelMode(QProcess::ForwardedChannels);

//    this->connectToHost();

//    return true;

//#else

    this->connectToHost();
    return true;

//#endif
}

void XyonController::connectToHost()
{
    socket->connectToHost("localhost", 2323);
}

void XyonController::playId(const QString &id)
{
    this->writeMethodParameter("get_stream_link", id);
}

void XyonController::writeMethodObject(const QString &method, const QJsonObject &value)
{
    this->writeJson(method, QJsonValue(value));
}

void XyonController::search(const QString &query)
{
    this->lastSearchQuery = query;
    this->page = 1;
    this->writeMethodObject("search", {{"search_query", query}, {"page", this->page}});
    this->emitChange();
}

void XyonController::loadMore()
{
    if (this->lastSearchQuery == "")
    {
        return;
    }

    this->page++;
    this->writeMethodObject("load_more", {{"search_query", this->lastSearchQuery}, {"page", this->page}});
    this->emitChange();
}

void XyonController::writeMethodParameter(const QString &method, const QString &parameter)
{
    this->writeJson(method, QJsonValue(parameter));
}

void XyonController::writeJson(const QString &method, const QJsonValue &value)
{
    QJsonObject obj {
        {"method", method},
        {"params", value}
    };

    QByteArray arr = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    arr.push_back('\n');

    qDebug() << "Sending" << arr;

    socket->write(arr);
}

void XyonController::resolveUrl(const AudioEntry &entry)
{
    this->entry = &entry;
    this->writeMethodParameter("resolve_url", entry.getId());
}

void XyonController::receive()
{
    QJsonDocument doc = QJsonDocument::fromJson(this->socket->readAll());
    //qDebug() << doc;
    if (doc.isObject())
    {
        QJsonObject rootObject = doc.object();
        if (!rootObject.contains("method") && !rootObject.contains("params"))
            return;

        QString method = rootObject["method"].toString();

        if (method == "response_search" || method == "response_load_more")
        {
            if (rootObject["params"].isArray())
            {
                if (method == "response_search")
                {
                    searchList->clear();
                }

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
                this->emitChange();
            }
        }
        else if (method == "response_get_stream_link")
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
        else if (method == "response_resolve_url")
        {
            if (rootObject["params"].isString() && this->entry != NULL)
            {
                this->playlist->urlResolved(*this->entry, QUrl(rootObject["params"].toString()));
                this->entry = NULL;
            }
        }
    }
}

void XyonController::test()
{
    this->player->setPosition(this->player->duration() / 2);
}

void XyonController::goNextPage()
{
    qDebug() << "Can go next page" << this->getCanGoNextPage();
    if (this->getCanGoNextPage())
    {
        this->setPage(this->page + 1);
        this->emitChange();

        QJsonObject obj {
            {"search_query", this->lastSearchQuery},
            {"page", this->page}
        };

        this->writeMethodObject("search", obj);
    }
}

void XyonController::goPreviousPage()
{
    qDebug() << "Can go previous page" << this->getCanGoPreviousPage();
    if (this->getCanGoPreviousPage())
    {
        this->setPage(this->page - 1);
        this->emitChange();
        QJsonObject obj {
            {"search_query", this->lastSearchQuery},
            {"page", this->page}
        };

        this->writeMethodObject("search", obj);
    }
}

XyonController::~XyonController()
{
    if (this->process != NULL)
    {
        this->process->terminate();
    }
}
