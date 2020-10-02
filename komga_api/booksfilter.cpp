#include "booksfilter.h"

BooksFilter::BooksFilter(QObject *parent): QObject{parent}
{

}

void BooksFilter::addTagFilter(QString &tag)
{
    if (! m_appliedTags.contains(tag)) {
        m_appliedTags.append(tag);
        emit filtersChanged();
    }
}

void BooksFilter::removeTagFilter(QString &tag)
{
    if (m_appliedTags.contains(tag)){
        m_appliedTags.removeAll(tag);
        emit filtersChanged();
    }
}

void BooksFilter::addReadStatus(QString &status)
{
    if (! m_filterReadStatuses.contains(status)) {
        m_filterReadStatuses.append(status);
        emit filtersChanged();
    }
}

void BooksFilter::removeReadStatus(QString &status)
{
    if (m_filterReadStatuses.contains(status)) {
        m_filterReadStatuses.removeAll(status);
        emit filtersChanged();
    }
}

QList<QString> BooksFilter::appliedTags() const
{
    return m_appliedTags;
}

QList<QString> BooksFilter::filterReadStatuses() const
{
    return m_filterReadStatuses;
}

QVariantList BooksFilter::filterTags() const
{
    QVariantList l;
    for (auto val : m_filterTags) {
        l.append(val);
    }
    return l;
}

void BooksFilter::setFilterTags(const QVariantList &filterTags)
{
    QList<QString> tags{};
    for (QVariant t : filterTags){
        tags.append(t.toString());
    }
    m_filterTags = tags;
    emit filterTagsChanged(filterTags);
}
