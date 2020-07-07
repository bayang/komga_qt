#include "searchresult.h"

SearchResult::SearchResult(QObject *parent) :
    QObject(parent)
{

}
int SearchResult::id() const
{
    return m_id;
}

void SearchResult::setId(int id)
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
