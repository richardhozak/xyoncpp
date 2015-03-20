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

private:
    QString id;
    QString title;
    QString type;

public:
    explicit AudioEntry(QObject *parent = 0);
    /*AudioEntry(QString id, QString title, QString type, QObject *parent = 0);*/

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

    static AudioEntry* fromJson(QJsonObject obj)
    {
        if (obj.contains("id") && obj.contains("title") && obj.contains("type"))
        {
            //SearchResult *searchResult = new SearchResult(obj["id"].toString(), obj["title"].toString(), obj["type"].toString());
            AudioEntry *audioEntry = new AudioEntry();
            audioEntry->id = obj["id"].toString();
            audioEntry->title = obj["title"].toString();
            audioEntry->type = obj["type"].toString();
            return audioEntry;
        }

        return NULL;
    }

signals:

public slots:
};

#endif // AUDIOENTRY_H
