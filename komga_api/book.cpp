#include "book.h"
#include <QDebug>

Book::Book(QObject *parent):
    QObject{parent}
{
    m_bookMetadata = new BookMetadata(this);
}

QString Book::id() const
{
    return m_id;
}

void Book::setId(QString id)
{
    m_id = id;
}

QString Book::seriesId() const
{
    return m_seriesId;
}

void Book::setSeriesId(QString seriesId)
{
    m_seriesId = seriesId;
}

QString Book::name() const
{
    return m_name;
}

void Book::setName(const QString &name)
{
    m_name = name;
}

QString Book::url() const
{
    return m_url;
}

void Book::setUrl(const QString &url)
{
    m_url = url;
}

int Book::number() const
{
    return m_number;
}

void Book::setNumber(int number)
{
    m_number = number;
}

qlonglong Book::sizeBytes() const
{
    return m_sizeBytes;
}

void Book::setSizeBytes(qlonglong sizeBytes)
{
    m_sizeBytes = sizeBytes;
}

QString Book::size() const
{
    return m_size;
}

void Book::setSize(const QString &size)
{
    m_size = size;
}

QString Book::mediaStatus() const
{
    return m_mediaStatus;
}

void Book::setMediaStatus(const QString &mediaStatus)
{
    m_mediaStatus = mediaStatus;
}

QString Book::mediaType() const
{
    return m_mediaType;
}
QString Book::mediaTypeShort() const
{
    if (m_mediaType.contains("zip", Qt::CaseInsensitive)) {
        return QString("CBZ");
    }
    else if (m_mediaType.contains("rar", Qt::CaseInsensitive)) {
        return QString("CBR");
    }
    else if (m_mediaType.contains("pdf", Qt::CaseInsensitive)) {
        return QString("PDF");
    }
    return QString("X");
}

void Book::setMediaType(const QString &mediaType)
{
    m_mediaType = mediaType;
}

int Book::pagesCount() const
{
    return m_pagesCount;
}

void Book::setPagesCount(int pagesCount)
{
    m_pagesCount = pagesCount;
}

BookMetadata* Book::bookMetadata() const
{
    return m_bookMetadata;
}

void Book::setBookMetadata(BookMetadata* &bookMetadata)
{
    m_bookMetadata = bookMetadata;
}

int Book::pageReached() const
{
    return m_pageReached;
}

void Book::setPageReached(int pageReached)
{
    if (pageReached != m_pageReached) {
        m_pageReached = pageReached;
        emit currentPageReachedChanged(m_pageReached);
    }
}

bool Book::completed() const
{
    return m_completed;
}

void Book::setCompleted(bool completed)
{
    m_completed = completed;
}
