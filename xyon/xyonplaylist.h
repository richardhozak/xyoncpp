#ifndef XYONPLAYLIST_H
#define XYONPLAYLIST_H

#include "qobjectlistmodel.h"
#include "audioentry.h"
#include <QObject>
#include <QMediaPlayer>

class XyonPlaylist : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentPlayingIndex READ getCurrentPlayingIndex NOTIFY currentPlayingIndexChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QObjectListModel *items READ getItems CONSTANT)
    Q_PROPERTY(QString playingTitle READ getPlayingTitle NOTIFY playingTitleChanged)
private:
    int currentPlayingIndex;
    int currentIndex;
    QObjectListModel *items;
    AudioEntry *resolvingEntry;
    QMediaPlayer *player;
    QString playingTitle;

public:
    explicit XyonPlaylist(QMediaPlayer *parent);

    int getCurrentPlayingIndex() const
    {
        return this->currentPlayingIndex;
    }

    int getCurrentIndex() const
    {
        return this->currentIndex;
    }

    QObjectListModel *getItems() const
    {
        return this->items;
    }

    QString getPlayingTitle() const
    {
        return this->playingTitle;
    }

private slots:
    void mediaPlayerStateChanged(QMediaPlayer::State state);
    void setPlayingTitle(const QString &title);
    void setCurrentPlayingIndex(int index);
    void playIndex(int index);

signals:
    void currentPlayingIndexChanged();
    void currentIndexChanged();
    void playingTitleChanged();
    void resolveUrl(const AudioEntry &entry);

public slots:
    void urlResolved(const AudioEntry &entry, const QUrl &url);
    void addYoutubeEntry(QObject *entry);
    void addLocalAudio(const QUrl &url);
    void setCurrentIndex(int index);
    void removeIndex(int index);
};

#endif // XYONPLAYLIST_H
