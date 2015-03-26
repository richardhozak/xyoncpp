#include "xyonplaylist.h"
#include <QDebug>

XyonPlaylist::XyonPlaylist(QMediaPlayer *parent)
    : QObject(parent)
    , currentIndex(-1)
    , resolvingEntry(0)
{
    this->player = parent;
    this->items = new QObjectListModel(this);
    this->resolvingEntry = NULL;

    connect(this->player, &QMediaPlayer::stateChanged, this, &XyonPlaylist::mediaPlayerStateChanged);
}

void XyonPlaylist::setCurrentIndex(int index)
{
    if (this->currentIndex != index)
    {
        this->currentIndex = index;
        emit this->currentIndexChanged();
    }
    this->playIndex(index);
}

void XyonPlaylist::playIndex(int index)
{
    if (index != -1 && index < this->items->count() && this->currentPlayingIndex != index)
    {
        AudioEntry *entry = static_cast<AudioEntry*>(this->items->at(this->currentIndex));

        qDebug() << entry->getType();

        if (entry->getType() == "youtube_audio")
        {
            qDebug() << "Resolving url";
            this->player->setMedia(QMediaContent());
            this->resolvingEntry = entry;
            this->setPlayingTitle(entry->getTitle());
            emit this->resolveUrl(*this->resolvingEntry);
        }
        else
        {
            this->player->setMedia(QUrl(entry->getId()));
            this->setPlayingTitle(entry->getTitle());
        }
    }
}

void XyonPlaylist::urlResolved(const AudioEntry &entry, const QUrl &url)
{
    qDebug() << "Url resolved";
    if (this->resolvingEntry != NULL && *this->resolvingEntry == entry)
    {
        qDebug() << "Url valid";
        this->resolvingEntry = NULL;

        this->player->setMedia(url);
        this->player->play();
        //qDebug() << this->player->errorString();
        //        if (this->player->state() != QMediaPlayer::StoppedState)
        //        {
        //            this->player->setMedia(url);
        //            this->player->play();
        //        }
        //        else
        //        {
        //            this->player->setMedia(url);
        //        }
    }
}

void XyonPlaylist::addYoutubeEntry(QObject *entry)
{
    qDebug() << entry;//entry.getTitle() << entry.getType();
    AudioEntry *audioEntry = dynamic_cast<AudioEntry*>(entry);
    if (audioEntry != NULL)
    {
        qDebug() << audioEntry->getTitle() << audioEntry->getType();
        if (audioEntry->getType() == "youtube_audio")
        {
            qDebug() << "Adding youtube entry";
            this->items->append(audioEntry);
        }
    }
}

void XyonPlaylist::addLocalAudio(const QUrl &url)
{
    Q_UNUSED(url)
}

void XyonPlaylist::setPlayingTitle(const QString &title)
{
    if (this->playingTitle != title)
    {
        this->playingTitle = title;
        emit this->playingTitleChanged();
    }
}

void XyonPlaylist::mediaPlayerStateChanged(QMediaPlayer::State state)
{
    switch (state)
    {
        case QMediaPlayer::StoppedState:
            this->setCurrentPlayingIndex(-1);
            break;
        case QMediaPlayer::PlayingState:
        case QMediaPlayer::PausedState:
            this->setCurrentPlayingIndex(this->currentIndex);
            break;
    }
}

void XyonPlaylist::setCurrentPlayingIndex(int index)
{
    if (this->currentPlayingIndex != index)
    {
        this->currentPlayingIndex = index;
        emit this->currentPlayingIndexChanged();
        qDebug() << this->player->errorString();
    }
}

void XyonPlaylist::removeIndex(int index)
{
    if (this->currentPlayingIndex == index)
    {
        this->player->stop();
        this->player->setMedia(QMediaContent());
        this->setCurrentPlayingIndex(-1);
        this->setPlayingTitle("");
    }
    if (index < this->items->count())
    {
        this->items->removeAt(index);
        if (this->currentIndex == 0 && this->items->count() > 0)
        {
            this->setCurrentIndex(0);
        }
        else if (this->currentIndex > 0)
        {
            this->setCurrentIndex(this->currentIndex - 1);
        }
        else
        {
            this->setCurrentIndex(-1);
        }
    }
}
