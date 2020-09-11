#include "series.h"

Series::Series(QObject *parent):
    QObject{parent}
{

}

QString Series::name() const {
    return m_name;
}
QString Series::id() const {
    return m_id;
}
QString Series::libraryId() const {
    return m_libraryId;
}
QString Series::url() const {
    return m_url;
}
int Series::booksCount() const {
    return m_booksCount;
}
void Series::setName(QString &name) {
    m_name = name;
}
void Series::setUrl(QString &url) {
    m_url = url;
}
void Series::setId(QString id) {
    m_id = id;
}
void Series::setLibraryId(QString id) {
    m_libraryId = id;
}
void Series::setBooksCount(int count) {
    if (count != m_booksCount) {
        m_booksCount = count;
        emit booksCountChanged(count);
    }
}

QString Series::metadataStatus() const
{
    return m_metadataStatus;
}

void Series::setMetadataStatus(const QString &metadataStatus)
{
    m_metadataStatus = metadataStatus;
}

QString Series::metadataTitle() const
{
    return m_metadataTitle;
}

void Series::setMetadataTitle(const QString &metadataTitle)
{
    m_metadataTitle = metadataTitle;
}

int Series::booksReadCount() const
{
    return m_booksReadCount;
}

void Series::setBooksReadCount(int booksReadCount)
{
    if (booksReadCount != m_booksReadCount) {
        m_booksReadCount = booksReadCount;
        emit booksReadCountChanged(booksReadCount);
    }
}

int Series::booksUnreadCount() const
{
    return m_booksUnreadCount;
}

void Series::setBooksUnreadCount(int booksUnreadCount)
{
    if (booksUnreadCount != m_booksUnreadCount) {
        m_booksUnreadCount = booksUnreadCount;
        emit booksUnreadCountChanged(booksUnreadCount);
    }
}

int Series::booksInProgressCount() const
{
    return m_booksInProgressCount;
}

void Series::setBooksInProgressCount(int booksInProgressCount)
{
    if (booksInProgressCount != m_booksInProgressCount) {
        m_booksInProgressCount = booksInProgressCount;
        emit booksInProgressCountChanged(m_booksInProgressCount);
    }
}

QString Series::metadataSummary() const
{
    return m_metadataSummary;
}

void Series::setMetadataSummary(const QString &metadataSummary)
{
    m_metadataSummary = metadataSummary;
}

QString Series::metadataReadingDirection() const
{
    return m_metadataReadingDirection;
}

void Series::setMetadataReadingDirection(const QString &metadataReadingDirection)
{
    m_metadataReadingDirection = metadataReadingDirection;
}

QString Series::metadataPublisher() const
{
    return m_metadataPublisher;
}

void Series::setMetadataPublisher(const QString &metadataPublisher)
{
    m_metadataPublisher = metadataPublisher;
}

QString Series::metadataAgeRating() const
{
    return m_metadataAgeRating;
}

void Series::setMetadataAgeRating(const QString &metadataAgeRating)
{
    m_metadataAgeRating = metadataAgeRating;
}

QString Series::metadataLanguage() const
{
    return m_metadataLanguage;
}

void Series::setMetadataLanguage(const QString &metadataLanguage)
{
    m_metadataLanguage = metadataLanguage;
}

QList<QString> Series::metadataGenres() const
{
    return m_metadataGenres;
}

void Series::setMetadataGenres(const QList<QString> &metadataGenres)
{
    m_metadataGenres = metadataGenres;
}

QList<QString> Series::metadataTags() const
{
    return m_metadataTags;
}

void Series::setMetadataTags(const QList<QString> &metadataTags)
{
    m_metadataTags = metadataTags;
}

QString Series::metadataCreated() const
{
    return m_metadataCreated;
}

void Series::setMetadataCreated(const QString &metadataCreated)
{
    m_metadataCreated = metadataCreated;
}

QString Series::metadataLastModified() const
{
    return m_metadataLastModified;
}

void Series::setMetadataLastModified(const QString &metadataLastModified)
{
    m_metadataLastModified = metadataLastModified;
}
