#ifndef SERIES_H
#define SERIES_H

#include <QString>
#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT Series: public QObject
{
    Q_OBJECT
    Q_PROPERTY( int ui_seriesId READ id CONSTANT )
    Q_PROPERTY( QString ui_seriesName READ name CONSTANT )

public:
    Series(QObject *parent = nullptr);
    QString name() const;
    int id() const;
    int libraryId() const;
    QString url() const;
    int booksCount() const;
    void setName(QString name);
    void setUrl(QString url);
    void setId(int id);
    void setLibraryId(int id);
    void setBooksCount(int count);

    QString metadataStatus() const;
    void setMetadataStatus(const QString &metadataStatus);

    QString metadataTitle() const;
    void setMetadataTitle(const QString &metadataTitle);

private:
    int m_id;
    int m_libraryId;
    int m_booksCount;
    QString m_name;
    QString m_url;
    QString m_metadataStatus;
    QString m_metadataTitle;
};

#endif // SERIES_H
