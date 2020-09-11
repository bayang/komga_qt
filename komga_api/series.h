#ifndef SERIES_H
#define SERIES_H

#include <QString>
#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT Series: public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_seriesId READ id NOTIFY idChanged )
    Q_PROPERTY( QString ui_seriesName READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY( int ui_seriesBooksCount READ booksCount WRITE setBooksCount NOTIFY booksCountChanged)
    Q_PROPERTY( int ui_seriesBooksReadCount READ booksReadCount WRITE setBooksReadCount NOTIFY booksReadCountChanged)
    Q_PROPERTY( int ui_seriesBooksUnreadCount READ booksUnreadCount WRITE setBooksUnreadCount NOTIFY booksUnreadCountChanged)
    Q_PROPERTY( int ui_seriesBooksInProgressCount READ booksInProgressCount WRITE setBooksInProgressCount NOTIFY booksInProgressCountChanged)
    Q_PROPERTY( QString ui_seriesMetadataStatus READ metadataStatus WRITE setMetadataStatus NOTIFY metadataStatusChanged )
    Q_PROPERTY( QString ui_seriesMetadataTitle READ metadataTitle )
    Q_PROPERTY( QString ui_seriesMetadataSummary READ metadataSummary WRITE setMetadataSummary NOTIFY metadataSummaryChanged )
    Q_PROPERTY( QString ui_seriesMetadataReadingDirection READ metadataReadingDirection WRITE setMetadataReadingDirection NOTIFY metadataReadingDirectionChanged )
    Q_PROPERTY( QString ui_seriesMetadataPublisher READ metadataPublisher WRITE setMetadataPublisher NOTIFY metadataPublisherChanged )
    Q_PROPERTY( QString ui_seriesMetadataAgeRating READ metadataAgeRating WRITE setMetadataAgeRating NOTIFY metadataAgeRatingChanged )
    Q_PROPERTY( QString ui_seriesMetadataLanguage READ metadataLanguage WRITE setMetadataLanguage NOTIFY metadataLanguageChanged )
    Q_PROPERTY( QList<QString> ui_seriesMetadataGenres READ metadataGenres WRITE setMetadataGenres NOTIFY metadataGenresChanged )
    Q_PROPERTY( QList<QString> ui_seriesMetadataTags READ metadataTags WRITE setMetadataTags NOTIFY metadataTagsChanged )

public:
    Series(QObject *parent = nullptr);
    QString name() const;
    QString id() const;
    QString libraryId() const;
    QString url() const;
    int booksCount() const;
    void setName(QString &name);
    void setUrl(QString &url);
    void setId(QString id);
    void setLibraryId(QString id);
    void setBooksCount(int count);

    QString metadataStatus() const;
    void setMetadataStatus(const QString &metadataStatus);

    QString metadataTitle() const;
    void setMetadataTitle(const QString &metadataTitle);

    int booksReadCount() const;
    void setBooksReadCount(int booksReadCount);

    int booksUnreadCount() const;
    void setBooksUnreadCount(int booksUnreadCount);

    int booksInProgressCount() const;
    void setBooksInProgressCount(int booksInProgressCount);

    QString metadataSummary() const;
    void setMetadataSummary(const QString &metadataSummary);

    QString metadataReadingDirection() const;
    void setMetadataReadingDirection(const QString &metadataReadingDirection);

    QString metadataPublisher() const;
    void setMetadataPublisher(const QString &metadataPublisher);

    QString metadataAgeRating() const;
    void setMetadataAgeRating(const QString &metadataAgeRating);

    QString metadataLanguage() const;
    void setMetadataLanguage(const QString &metadataLanguage);

    QList<QString> metadataGenres() const;
    void setMetadataGenres(const QList<QString> &metadataGenres);

    QList<QString> metadataTags() const;
    void setMetadataTags(const QList<QString> &metadataTags);

    QString metadataCreated() const;
    void setMetadataCreated(const QString &metadataCreated);

    QString metadataLastModified() const;
    void setMetadataLastModified(const QString &metadataLastModified);

signals:
    void metadataStatusChanged();
    void nameChanged();
    void idChanged();
    void booksCountChanged(int count);
    void booksReadCountChanged(int count);
    void booksUnreadCountChanged(int count);
    void booksInProgressCountChanged(int count);
    void metadataSummaryChanged();
    void metadataReadingDirectionChanged();
    void metadataPublisherChanged();
    void metadataAgeRatingChanged();
    void metadataLanguageChanged();
    void metadataGenresChanged();
    void metadataTagsChanged();

private:
    QString m_id{};
    QString m_libraryId{};
    int m_booksCount{};
    int m_booksReadCount{};
    int m_booksUnreadCount{};
    int m_booksInProgressCount{};
    QString m_name{};
    QString m_url{};
    QString m_metadataStatus{};
    QString m_metadataTitle{};
    QString m_metadataSummary{};
    QString m_metadataReadingDirection{};
    QString m_metadataPublisher{};
    QString m_metadataAgeRating{};
    QString m_metadataLanguage{};
    QList<QString> m_metadataGenres{};
    QList<QString> m_metadataTags{};
    QString m_metadataCreated{};
    QString m_metadataLastModified{};
};

#endif // SERIES_H
