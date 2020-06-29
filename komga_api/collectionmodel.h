#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include "komga_api_global.h"
#include "komga_api.h"
#include "collection.h"
#include <QObject>
#include <QAbstractListModel>
#include <QJsonDocument>

class KOMGA_API_EXPORT CollectionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CollectionModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum CollectionRoles {
        IdRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        OrderedRole = Qt::UserRole + 3,
        FilteredRole = Qt::UserRole + 4,
        SeriesIdsRole = Qt::UserRole + 5,
    };
    Q_INVOKABLE void loadCollections();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void nextCollectionsPage();

public slots:
    void apiDataReceived(QJsonObject page);

private:
    Komga_api* m_api = nullptr;
    QList<Collection*> m_collections{};
    int m_currentPageNumber{};
    int m_totalPageNumber{};
};

#endif // COLLECTIONMODEL_H
