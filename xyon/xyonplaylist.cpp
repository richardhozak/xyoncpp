#include "xyonplaylist.h"
#include <QDebug>

XyonPlaylist::XyonPlaylist(QMediaPlayer *parent)
    : QObject(parent)
    , currentIndex(0)
    , resolvingEntry(0)
{
    this->player = parent;
    this->items = new QObjectListModel(this);
    this->resolvingEntry = NULL;
}

void XyonPlaylist::setCurrentIndex(int index)
{
    if (this->currentIndex != index && index < this->items->count())
    {
        this->currentIndex = index;
        emit this->currentIndexChanged();

        AudioEntry *entry = static_cast<AudioEntry*>(this->items->at(this->currentIndex));

        if (entry->getType() == "youtube")
        {
            this->resolvingEntry = entry;
            emit this->resolveUrl(*this->resolvingEntry);
        }
        else
        {
            this->player->setMedia(QUrl(entry->getId()));
        }
    }
}

void XyonPlaylist::urlResolved(const AudioEntry &entry, const QUrl &url)
{
    if (this->resolvingEntry != NULL && *this->resolvingEntry == entry)
    {
        this->resolvingEntry = NULL;
        this->player->setMedia(url);
    }
}

void XyonPlaylist::addYoutubeEntry(QObject *entry)
{
    qDebug() << entry;//entry.getTitle() << entry.getType();
    AudioEntry *audioEntry = dynamic_cast<AudioEntry*>(entry);
    if (audioEntry != NULL)
    {
        qDebug() << audioEntry->getTitle() << audioEntry->getType();
        if (audioEntry->getType() == "youtube")
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
