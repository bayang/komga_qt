#include "searchresult.h"

SearchResult::SearchResult(QObject *parent) :
    QObject(parent)
{

}
QString SearchResult::id() const
{
    return m_id;
}

void SearchResult::setId(QString id)
{
    m_id = id;
}

QString SearchResult::name() const
{
    return m_name;
}

void SearchResult::setName(const QString &name)
{
    m_name = name;
}


SearchResult::ResultType SearchResult::resultType() const
{
    return m_resultType;
}

void SearchResult::setResultType(const ResultType &resultType)
{
    m_resultType = resultType;
}

Book *SearchResult::book() const
{
    return m_book;
}

void SearchResult::setBook(Book *book)
{
    m_book = book;
}

Series *SearchResult::series() const
{
    return m_series;
}

void SearchResult::setSeries(Series *series)
{
    m_series = series;
}

Collection *SearchResult::collection() const
{
    return m_collection;
}

void SearchResult::setCollection(Collection *collection)
{
    m_collection = collection;
}

ReadList *SearchResult::readList() const
{
    return m_readList;
}

void SearchResult::setReadList(ReadList *readList)
{
    m_readList = readList;
}
