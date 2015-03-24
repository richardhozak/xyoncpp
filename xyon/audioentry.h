#ifndef AUDIOENTRY_H
#define AUDIOENTRY_H

#include <QObject>
#include <QJsonObject>

class AudioEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString type READ getType CONSTANT)
    Q_PROPERTY(QString time READ getTime CONSTANT)

private:
    QString id;
    QString title;
    QString type;
    QString time;

public:
    explicit AudioEntry(QObject *parent = 0);
    AudioEntry(QString id, QString title, QString type, QString time, QObject *parent = 0);

    QString getId() const
    {
        return this->id;
    }

    QString getTitle() const
    {
        return this->title;
    }

    QString getType() const
    {
        return this->type;
    }

    QString getTime() const
    {
        return this->time;
    }

    static AudioEntry* fromJson(QJsonObject obj)
    {
        if (obj.contains("id") && obj.contains("title") && obj.contains("type") && obj.contains("time"))
        {
            //SearchResult *searchResult = new SearchResult(obj["id"].toString(), obj["title"].toString(), obj["type"].toString());
            AudioEntry *audioEntry = new AudioEntry();
            audioEntry->id = obj["id"].toString();
            audioEntry->title = obj["title"].toString();
            audioEntry->type = obj["type"].toString();
            audioEntry->time = obj["time"].toString();
            return audioEntry;
        }

        return NULL;
    }

    bool operator ==(AudioEntry const &entry);

signals:

public slots:
};

#endif // AUDIOENTRY_H
