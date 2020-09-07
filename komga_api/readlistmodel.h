#ifndef READLISTMODEL_H
#define READLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "komga_api.h"
#include "readlist.h"

class ReadListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ReadListModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum ReadListRoles {
        IdRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        FilteredRole = Qt::UserRole + 3,
        BooksIdsRole = Qt::UserRole + 4,
        SizeRole = Qt::UserRole + 5,
    };
    Q_INVOKABLE void loadReadLists();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void nextReadListsPage();
public slots:
    void apiDataReceived(QJsonObject page);

private:
    Komga_api* m_api = nullptr;
    QList<ReadList*> m_readLists{};
    int m_currentPageNumber{};
    int m_totalPageNumber{};

};

#endif // READLISTMODEL_H
