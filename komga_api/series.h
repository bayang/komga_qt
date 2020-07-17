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

signals:
    void metadataStatusChanged();
    void nameChanged();
    void idChanged();
    void booksCountChanged(int count);
    void booksReadCountChanged(int count);
    void booksUnreadCountChanged(int count);
    void booksInProgressCountChanged(int count);

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
};

#endif // SERIES_H
