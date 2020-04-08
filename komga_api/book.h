#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QObject>
#include "bookmetadata.h"
#include "komga_api_global.h"

/**
{
      "id": 5,
      "seriesId": 3,
      "name": "Figurec",
      "url": "/home/ubik/Documents/cmx/Figurec.cbr",
      "number": 1,
      "created": "2020-03-31T16:13:03",
      "lastModified": "2020-03-31T16:13:05",
      "fileLastModified": "2019-12-15T12:01:30",
      "sizeBytes": 32649953,
      "size": "31,1 MiB",
      "media": {
        "status": "READY",
        "mediaType": "application/x-rar-compressed",
        "pagesCount": 74,
        "comment": ""
      },
      "metadata": {
        "title": "Figurec",
        "titleLock": false,
        "summary": "",
        "summaryLock": false,
        "number": "1",
        "numberLock": false,
        "numberSort": 1,
        "numberSortLock": false,
        "readingDirection": "",
        "readingDirectionLock": false,
        "publisher": "",
        "publisherLock": false,
        "ageRating": null,
        "ageRatingLock": false,
        "releaseDate": null,
        "releaseDateLock": false,
        "authors": [],
        "authorsLock": false
      }
    }
 **/

class KOMGA_API_EXPORT Book: public QObject
{
    Q_OBJECT
public:
    Book(QObject *parent = nullptr);

    int id() const;
    void setId(int id);

    int seriesId() const;
    void setSeriesId(int seriesId);

    QString name() const;
    void setName(const QString &name);

    QString url() const;
    void setUrl(const QString &url);

    int number() const;
    void setNumber(int number);

    qlonglong sizeBytes() const;
    void setSizeBytes(qlonglong sizeBytes);

    QString size() const;
    void setSize(const QString &size);

    QString mediaStatus() const;
    void setMediaStatus(const QString &mediaStatus);

    QString mediaType() const;
    void setMediaType(const QString &mediaType);

    int pagesCount() const;
    void setPagesCount(int pagesCount);

    BookMetadata bookMetadata() const;
    void setBookMetadata(const BookMetadata &bookMetadata);

private:
    int m_id;
    int m_seriesId;
    QString m_name;
    QString m_url;
    int m_number;
    qlonglong m_sizeBytes;
    QString m_size;
    QString m_mediaStatus;
    QString m_mediaType;
    int m_pagesCount;
    BookMetadata m_bookMetadata;
};

#endif // BOOK_H
