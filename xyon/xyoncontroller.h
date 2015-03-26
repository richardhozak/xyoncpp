#ifndef XYONCONTROLLER_H
#define XYONCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QQmlContext>
#include <QMediaPlayer>
#include <QProcess>

#include "qobjectlistmodel.h"
#include "xyonplaylist.h"


class XyonController : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QObjectListModel *searchList READ getSearchList CONSTANT)
    Q_PROPERTY(bool canGoPreviousPage READ getCanGoPreviousPage NOTIFY canGoPreviousPageChanged)
    Q_PROPERTY(bool canGoNextPage READ getCanGoNextPage NOTIFY canGoNextPageChanged)
    Q_PROPERTY(int page READ getPage NOTIFY pageChanged)
    Q_PROPERTY(XyonPlaylist *playlist READ getPlaylist CONSTANT)
private:
    QObjectListModel *searchList;
    QTcpSocket *socket;
    QMediaPlayer *player;
    QString lastSearchQuery;
    const AudioEntry *entry;

    QProcess *process;

    int page;
    XyonPlaylist *playlist;

    void resolveUrl(const AudioEntry &entry);

    void setPage(int page)
    {
        if (this->page != page)
        {
            this->page = page;
            emit this->pageChanged();
        }
    }

    void emitChange()
    {
        emit this->canGoNextPageChanged();
        emit this->canGoPreviousPageChanged();
    }

    void connectToHost();

public:
    explicit XyonController(QQmlContext *context, QObject *parent = 0);

    Q_INVOKABLE void playId(const QString &id);
    Q_INVOKABLE void search(const QString &query);
    void writeMethodObject(const QString &method, const QJsonObject &value);
    void writeMethodParameter(const QString &method, const QString &paremeter);
    void writeJson(const QString &method, const QJsonValue &value);
    void receive();
    Q_INVOKABLE void test();
    Q_INVOKABLE void goNextPage();
    Q_INVOKABLE void goPreviousPage();


    bool getCanGoPreviousPage() const
    {
        if (this->page <= 1)
        {
            return false;
        }
        if (this->searchList->count() > 0)
        {
            return true;
        }

        return false;
    }

    bool getCanGoNextPage() const
    {
        return this->searchList->count() > 0;
    }

    int getPage() const
    {
        return this->page;
    }

    XyonPlaylist *getPlaylist() const
    {
        return this->playlist;
    }

    bool initializeController();

    ~XyonController();

signals:
    void canGoPreviousPageChanged();
    void canGoNextPageChanged();
    void pageChanged();

public slots:
    void loadMore();

};

#endif // XYONCONTROLLER_H
