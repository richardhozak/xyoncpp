#include "audioentry.h"
#include <QDebug>

AudioEntry::AudioEntry(QObject *parent) : QObject(parent) { }

AudioEntry::AudioEntry(QString id, QString title, QString type, QString time, QObject *parent)
    : QObject(parent)
    , id(id)
    , title(title)
    , type(type)
    , time(time)
{

}

bool AudioEntry::operator ==(AudioEntry const &entry)
{
    //qDebug() << "Comparing audio entries";
    return &entry != NULL && this->id == entry.id;
}


