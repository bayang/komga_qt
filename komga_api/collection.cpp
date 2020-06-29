#include "collection.h"

Collection::Collection(QObject *parent) : QObject(parent)
{

}

int Collection::id() const
{
    return m_id;
}

void Collection::setId(int id)
{
    m_id = id;
}

QString Collection::name() const
{
    return m_name;
}

void Collection::setName(const QString &name)
{
    m_name = name;
}

bool Collection::ordered() const
{
    return m_ordered;
}

void Collection::setOrdered(bool ordered)
{
    m_ordered = ordered;
}

bool Collection::filtered() const
{
    return m_filtered;
}

void Collection::setFiltered(bool filtered)
{
    m_filtered = filtered;
}

QList<int> Collection::seriesIds() const
{
    return m_seriesIds;
}

void Collection::setSeriesIds(const QList<int> &seriesIds)
{
    m_seriesIds = seriesIds;
}
