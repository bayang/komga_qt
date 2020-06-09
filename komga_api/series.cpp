#include "series.h"

Series::Series(QObject *parent):
    QObject{parent}
{

}

QString Series::name() const {
    return m_name;
}
int Series::id() const {
    return m_id;
}
int Series::libraryId() const {
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
void Series::setId(int id) {
    m_id = id;
}
void Series::setLibraryId(int id) {
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
