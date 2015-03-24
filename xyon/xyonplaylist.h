#ifndef XYONPLAYLIST_H
#define XYONPLAYLIST_H

#include "qobjectlistmodel.h"
#include "audioentry.h"
#include <QObject>
#include <QMediaPlayer>

class XyonPlaylist : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QObjectListModel *items READ getItems CONSTANT)
private:
    int currentIndex;
    QObjectListModel *items;
    AudioEntry *resolvingEntry;
    QMediaPlayer *player;
public:
    explicit XyonPlaylist(QMediaPlayer *parent);
    Q_INVOKABLE void addLocalAudio(const QUrl &url);
    //Q_INVOKABLE void addYoutubeAudio(const QString &id);
    Q_INVOKABLE void addYoutubeEntry(QObject *entry);
    void setCurrentIndex(int index);

    int getCurrentIndex() const
    {
        return this->currentIndex;
    }

    QObjectListModel *getItems() const
    {
        return this->items;
    }


signals:
    void currentIndexChanged();
    void resolveUrl(const AudioEntry &entry);

public slots:
    void urlResolved(const AudioEntry &entry, const QUrl &url);
};

#endif // XYONPLAYLIST_H
