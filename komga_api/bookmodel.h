#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QAbstractListModel>
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
    };
private slots:
    void apiDataReceived(QList<Book*> books);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void loadBooks(int seriesId);
    Q_INVOKABLE Book* get(int index);
    QByteArray getThumbnail(int id);

private:
    Komga_api* m_api;
    QList<Book*> m_books;
};

#endif // BOOKMODEL_H
