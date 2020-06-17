#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>
#include <QCache>
#include "komga_api_global.h"
#include "komga_api.h"

class KOMGA_API_EXPORT BookModel : public QAbstractListModel
{
    Q_OBJECT

public:
    BookModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum BooksRoles {
        IdRole = Qt::UserRole + 1,
        SeriesIdRole = Qt::UserRole + 2,
        NameRole = Qt::UserRole + 3,
        NumberRole = Qt::UserRole + 4,
        UrlRole = Qt::UserRole + 5,
        SizeBytesRole = Qt::UserRole + 6,
        SizeRole = Qt::UserRole + 7,
        MediaStatusRole = Qt::UserRole + 8,
        MediaTypeRole = Qt::UserRole + 9,
        PageCountRole = Qt::UserRole + 10,
        SummaryRole = Qt::UserRole + 11,
        PublisherRole = Qt::UserRole + 12,
        ReleaseDateRole = Qt::UserRole + 13,
        AuthorsRole = Qt::UserRole + 14,
        AgeRatingRole = Qt::UserRole + 15,
        TitleRole = Qt::UserRole + 16,
        MediaTypeFullRole = Qt::UserRole + 17,
        PageReachedRole = Qt::UserRole + 18,
        CompletedRole = Qt::UserRole + 19,
    };
public slots:
    void apiDataReceived(QJsonObject books);
    void preloadImageDataReceived(QPair<QString, QByteArray> res);
    void updateProgress(int bookId, int page, bool completed = false);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void loadBooks(Series* series);
//    Q_INVOKABLE Book* get(int index);
    QByteArray getThumbnail(int id);
    QByteArray getPage(int id, int pageNum);
    void nextBooksPage(Series *series);
    void resetBooks();
    void preloadPage(int id, int pageNum);
    QByteArray* getImageFromCache(const QString &key);

    Book *parseBook(const QJsonValue &value);
    bool setData(const QModelIndex& index, const QVariant& value,
                 int role);

signals:
    void refresh();

private:
    Komga_api* m_api = nullptr;
    QList<Book*> m_books{};
    int m_currentPageNumber{};
    int m_totalPageNumber{};
    QCache<QString, QByteArray> m_picturesCache{50};
};

#endif // BOOKMODEL_H
