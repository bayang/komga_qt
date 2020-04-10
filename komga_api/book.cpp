#include "book.h"

Book::Book(QObject *parent):
    QObject{parent}
{

}

int Book::id() const
{
    return m_id;
}

void Book::setId(int id)
{
    m_id = id;
}

int Book::seriesId() const
{
    return m_seriesId;
}

void Book::setSeriesId(int seriesId)
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
