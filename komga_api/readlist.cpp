#include "readlist.h"

ReadList::ReadList(QObject *parent) : QObject(parent)
{

}

QString ReadList::id() const
{
    return m_id;
}

void ReadList::setId(QString id)
{
    m_id = id;
}

QString ReadList::name() const
{
    return m_name;
}

void ReadList::setName(const QString &name)
{
    m_name = name;
}

bool ReadList::filtered() const
{
    return m_filtered;
}

void ReadList::setFiltered(bool filtered)
{
    m_filtered = filtered;
}

QList<QString> ReadList::booksIds() const
{
    return m_booksIds;
}

void ReadList::setBooksIds(const QList<QString> &booksIds)
{
    m_booksIds = booksIds;
}

int ReadList::booksIdsSize()
{
    return m_booksIds.count();
}
