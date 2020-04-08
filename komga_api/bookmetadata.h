#ifndef BOOKMETADATA_H
#define BOOKMETADATA_H

#include <QString>
#include <QList>
#include "komga_api_global.h"

/**
 *
 * "metadata": {
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
 *
 *
 */


class KOMGA_API_EXPORT BookMetadata
{
public:
    BookMetadata();
    QString title() const;
    void setTitle(const QString &title);
    bool titleLock() const;


    QString readingDirection() const;
    void setReadingDirection(const QString &readingDirection);

    void setTitleLock(bool titleLock);

    QString summary() const;
    void setSummary(const QString &summary);

    bool summaryLock() const;
    void setSummaryLock(bool summaryLock);

    QString number() const;
    void setNumber(const QString &number);

    bool numberLock() const;
    void setNumberLock(bool numberLock);

    int numberSort() const;
    void setNumberSort(int numberSort);

    bool numberSortLock() const;
    void setNumberSortLock(bool numberSortLock);

    bool readingDirectionLock() const;
    void setReadingDirectionLock(bool readingDirectionLock);

    QString publisher() const;
    void setPublisher(const QString &publisher);

    bool publisherLock() const;
    void setPublisherLock(bool publisherLock);

    QString ageRating() const;
    void setAgeRating(const QString &ageRating);

    bool ageRatingLock() const;
    void setAgeRatingLock(bool ageRatingLock);

    QString releaseDate() const;
    void setReleaseDate(const QString &releaseDate);

    bool releaseDateLock() const;
    void setReleaseDateLock(bool releaseDateLock);

    QList<QString> authors() const;
    void setAuthors(const QList<QString> &authors);

    bool authorsLock() const;
    void setAuthorsLock(bool authorsLock);

private:
    QString m_title;
    bool m_titleLock;
    QString m_summary;
    bool m_summaryLock;
    QString m_number;
    bool m_numberLock;
    int m_numberSort;
    bool m_numberSortLock;
    QString m_readingDirection;
    bool m_readingDirectionLock;
    QString m_publisher;
    bool m_publisherLock;
    QString m_ageRating;
    bool m_ageRatingLock;
    QString m_releaseDate;
    bool m_releaseDateLock;
    QList<QString> m_authors;
    bool m_authorsLock;

};

#endif // BOOKMETADATA_H
