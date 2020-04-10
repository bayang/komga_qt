#include "bookmetadata.h"

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

QString BookMetadata::publisher() const
{
    return m_publisher;
}

void BookMetadata::setPublisher(const QString &publisher)
{
    m_publisher = publisher;
}

bool BookMetadata::publisherLock() const
{
    return m_publisherLock;
}

void BookMetadata::setPublisherLock(bool publisherLock)
{
    m_publisherLock = publisherLock;
}

QString BookMetadata::ageRating() const
{
    return m_ageRating;
}

void BookMetadata::setAgeRating(const QString &ageRating)
{
    m_ageRating = ageRating;
}

bool BookMetadata::ageRatingLock() const
{
    return m_ageRatingLock;
}

void BookMetadata::setAgeRatingLock(bool ageRatingLock)
{
    m_ageRatingLock = ageRatingLock;
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

QList<QString> BookMetadata::authors() const
{
    return m_authors;
}

void BookMetadata::setAuthors(const QList<QString> &authors)
{
    m_authors = authors;
}

bool BookMetadata::authorsLock() const
{
    return m_authorsLock;
}

void BookMetadata::setAuthorsLock(bool authorsLock)
{
    m_authorsLock = authorsLock;
}
