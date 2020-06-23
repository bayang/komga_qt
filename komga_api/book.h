#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QObject>
#include "bookmetadata.h"
#include "komga_api_global.h"

class KOMGA_API_EXPORT Book: public QObject
{
    Q_OBJECT
    Q_PROPERTY( int ui_bookId READ id CONSTANT )
    Q_PROPERTY( QString ui_bookName READ name CONSTANT )
    Q_PROPERTY( QString ui_bookUrl READ url CONSTANT )
    Q_PROPERTY( int ui_bookNumber READ number CONSTANT )
    Q_PROPERTY( QString ui_bookSize READ size CONSTANT )
    Q_PROPERTY( QString ui_bookMediaStatus READ mediaStatus CONSTANT )
    Q_PROPERTY( QString ui_bookMediaType READ mediaType CONSTANT )
    Q_PROPERTY( QString ui_bookShortMediaType READ mediaTypeShort CONSTANT )
    Q_PROPERTY( int ui_bookPagesCount READ pagesCount CONSTANT )
    Q_PROPERTY( int ui_bookPageReached READ pageReached WRITE setPageReached NOTIFY currentPageReachedChanged )
    Q_PROPERTY( bool ui_bookCompleted READ completed CONSTANT )
    Q_PROPERTY( BookMetadata* ui_bookMetadata READ bookMetadata CONSTANT )
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

    QString mediaTypeShort() const;

    int pagesCount() const;
    void setPagesCount(int pagesCount);

    BookMetadata* bookMetadata() const;
    void setBookMetadata(BookMetadata* &bookMetadata);

    int pageReached() const;
    void setPageReached(int pageReached);

    bool completed() const;
    void setCompleted(bool completed);

signals:
    void currentPageReachedChanged(int page);

private:
    int m_id {};
    int m_seriesId {};
    QString m_name{};
    QString m_url{};
    int m_number {};
    qlonglong m_sizeBytes{};
    QString m_size{};
    QString m_mediaStatus{};
    QString m_mediaType{};
    int m_pagesCount {};
    int m_pageReached {};
    bool m_completed{false};
    BookMetadata* m_bookMetadata = nullptr;
};

#endif // BOOK_H
