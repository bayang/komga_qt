#include "bookmetadata.h"
#include <QDebug>

BookMetadata::BookMetadata(QObject *parent):
    QObject{parent}
{

}
void BookMetadata::setTitle(const QString &title) {
    m_title = title;
}
QString BookMetadata::title() const {
    return m_title;
}

bool BookMetadata::titleLock() const {
    return m_titleLock;
}
QString BookMetadata::readingDirection() const
{
    return m_readingDirection;
}

void BookMetadata::setReadingDirection(const QString &readingDirection)
{
    m_readingDirection = readingDirection;
}

void BookMetadata::setTitleLock(bool titleLock)
{
    m_titleLock = titleLock;
}

QString BookMetadata::summary() const
{
    return m_summary;
}

void BookMetadata::setSummary(const QString &summary)
{
    m_summary = summary;
}

bool BookMetadata::summaryLock() const
{
    return m_summaryLock;
}

void BookMetadata::setSummaryLock(bool summaryLock)
{
    m_summaryLock = summaryLock;
}

QString BookMetadata::number() const
{
    return m_number;
}

void BookMetadata::setNumber(const QString &number)
{
    m_number = number;
}

bool BookMetadata::numberLock() const
{
    return m_numberLock;
}

void BookMetadata::setNumberLock(bool numberLock)
{
    m_numberLock = numberLock;
}

int BookMetadata::numberSort() const
{
    return m_numberSort;
}

void BookMetadata::setNumberSort(int numberSort)
{
    m_numberSort = numberSort;
}

bool BookMetadata::numberSortLock() const
{
    return m_numberSortLock;
}

void BookMetadata::setNumberSortLock(bool numberSortLock)
{
    m_numberSortLock = numberSortLock;
}

bool BookMetadata::readingDirectionLock() const
{
    return m_readingDirectionLock;
}

void BookMetadata::setReadingDirectionLock(bool readingDirectionLock)
{
    m_readingDirectionLock = readingDirectionLock;
}

QString BookMetadata::releaseDate() const
{
    return m_releaseDate;
}

void BookMetadata::setReleaseDate(const QString &releaseDate)
{
    m_releaseDate = releaseDate;
}

bool BookMetadata::releaseDateLock() const
{
    return m_releaseDateLock;
}

void BookMetadata::setReleaseDateLock(bool releaseDateLock)
{
    m_releaseDateLock = releaseDateLock;
}

QList<Author*> BookMetadata::authors() const
{
    return m_authors;
}

void BookMetadata::setAuthors(const QList<Author*> &authors)
{
    m_authors = authors;
    emit writersChanged();
}

bool BookMetadata::authorsLock() const
{
    return m_authorsLock;
}

void BookMetadata::setAuthorsLock(bool authorsLock)
{
    m_authorsLock = authorsLock;
}
QString BookMetadata::writersAsString() const {
    QString auth = "";
    for (Author* a: m_authors) {
        if (a->role() == "writer") {
            auth += a->name();
            auth += " ";
        }
    }
    return auth;
}
QString BookMetadata::coloristsAsString() const {
    QString auth = "";
    for (Author* a: m_authors) {
        if (a->role() == "colorist") {
            auth += a->name();
            auth += " ";
        }
    }
    return auth;
}

QVariantList BookMetadata::tags() const
{
    QVariantList l;
    for (auto val : m_tags) {
        l.append(val);
    }
    return l;
}

void BookMetadata::setTags(const QVariantList &tags)
{
    QList<QString> tagsList{};
    for (QVariant t : tags){
        tagsList.append(t.toString());
    }
    m_tags = tagsList;
    emit bookTagsChanged(tags);
}
QString BookMetadata::pencillersAsString() const {
    QString auth = "";
    for (Author* a: m_authors) {
        if (a->role() == "penciller") {
            auth += a->name();
            auth += " ";
        }
    }
    return auth;
}
