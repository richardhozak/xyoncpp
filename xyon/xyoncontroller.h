#ifndef XYONCONTROLLER_H
#define XYONCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <QQmlContext>
#include <QMediaPlayer>

#include "qobjectlistmodel.h"


class XyonController : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QObjectListModel *searchList READ getSearchList CONSTANT)
private:
    QObjectListModel *searchList;
    QTcpSocket *socket;
    QMediaPlayer *player;
public:
    explicit XyonController(QQmlContext *context, QObject *parent = 0);

    Q_INVOKABLE void playId(const QString &id);
    Q_INVOKABLE void search(const QString &query);
    void writeMethod(const QString &method, const QString &query);
    void receive();
    Q_INVOKABLE void test();

//    QObjectListModel *getSearchList() const
//    {
//        return this->searchList;
//    }

signals:

public slots:


};

#endif // XYONCONTROLLER_H
