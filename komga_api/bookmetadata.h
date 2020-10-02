#ifndef BOOKMETADATA_H
#define BOOKMETADATA_H

#include <QString>
#include <QObject>
#include <QList>
#include "komga_api_global.h"
#include "author.h"

class KOMGA_API_EXPORT BookMetadata: public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_metadataTitle READ title CONSTANT )
    Q_PROPERTY( QString ui_metadataSummary READ summary CONSTANT )
    Q_PROPERTY( QString ui_metadataNumber READ number CONSTANT )
    Q_PROPERTY( QString ui_metadataWriters READ writersAsString NOTIFY writersChanged)
    Q_PROPERTY( QString ui_metadataPencillers READ pencillersAsString NOTIFY pencillersChanged)
    Q_PROPERTY( QString ui_metadataColorists READ coloristsAsString NOTIFY coloristsChanged)
    Q_PROPERTY( QString ui_metadataReleaseDate READ releaseDate CONSTANT )
    Q_PROPERTY( QVariantList ui_metadataTags READ tags WRITE setTags NOTIFY bookTagsChanged )

public:
    BookMetadata(QObject *parent = nullptr);
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

    QString releaseDate() const;
    void setReleaseDate(const QString &releaseDate);

    bool releaseDateLock() const;
    void setReleaseDateLock(bool releaseDateLock);

    QList<Author*> authors() const;
    void setAuthors(const QList<Author*> &authors);

    bool authorsLock() const;
    void setAuthorsLock(bool authorsLock);

    QString writersAsString() const;
    QString pencillersAsString() const;
    QString coloristsAsString() const;

    QVariantList tags() const;
    void setTags(const QVariantList &tags);

signals:
    void writersChanged();
    void pencillersChanged();
    void coloristsChanged();
    void bookTagsChanged(QVariantList tags);

private:
    QString m_title{};
    bool m_titleLock{};
    QString m_summary{};
    bool m_summaryLock{};
    QString m_number{};
    bool m_numberLock{};
    int m_numberSort{};
    bool m_numberSortLock{};
    QString m_readingDirection{};
    bool m_readingDirectionLock{};
    QString m_releaseDate{};
    bool m_releaseDateLock{};
    QList<Author*> m_authors{};
    bool m_authorsLock{};
    QList<QString> m_tags{};
};

#endif // BOOKMETADATA_H
