#include "collectionmodel.h"
#include <QJsonArray>

CollectionModel::CollectionModel(QObject *parent, Komga_api* api) :
       QAbstractListModel{parent}, m_api{api}
{
    connect(m_api, &Komga_api::collectionsDataReady,
            this, &CollectionModel::apiDataReceived);
    connect(m_api, &Komga_api::seriesCollectionsDataReady,
            this, &CollectionModel::seriesCollectionsReceived);
}

void CollectionModel::loadCollections()
{
    qDebug() << "load collections";
    m_api->getCollections();
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_collections.count();
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
    if (! index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_collections.count())
        return QVariant();

    const Collection* collection = m_collections[index.row()];
    if (role == IdRole) {
        return collection->id();
    }
    else if (role == NameRole) {
        return collection->name();
    }
    else if (role == OrderedRole) {
        return collection->ordered();
    }
    else if (role == FilteredRole) {
        return collection->filtered();
    }
    else if (role == SeriesIdsRole) {
        return QVariant::fromValue(collection->seriesIds());
    }
    else if (role == SizeRole) {
        return collection->seriesIds().count();
    }
    return QVariant();
}

QHash<int, QByteArray> CollectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[IdRole] = "collectionId";
        roles[NameRole] = "collectionName";
        roles[SeriesIdsRole] = "collectionSeriesId";
        roles[FilteredRole] = "collectionFiltered";
        roles[OrderedRole] = "collectionOrdered";
        roles[SizeRole] = "collectionSize";
        return roles;
}

void CollectionModel::nextCollectionsPage()
{
    qDebug() << "curr p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getCollections(m_currentPageNumber + 1);
    }
}

void CollectionModel::apiDataReceived(QJsonObject page)
{
    qDebug() << "received collections " << page;
    int pageNum = page["number"].toInt();
    int totPages = page["totalPages"].toInt();
    int nbElems = page["numberOfElements"].toInt();
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_collections.size(), m_collections.size() + nbElems - 1);
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                Collection* c = new Collection(this);
                QJsonObject jsob = value.toObject();
                c->setId(jsob["id"].toString());
                c->setName(jsob["name"].toString());
                c->setOrdered(jsob["ordered"].toBool());
                c->setFiltered(jsob["filtered"].toBool());
                QJsonArray seriesArray = jsob["seriesIds"].toArray();
                foreach (const QJsonValue &val, seriesArray) {
                    c->seriesIds().append(val.toString());
                }
                m_collections.append(std::move(c));
            }
            emit endInsertRows();
        }
        else {
            emit beginResetModel();
            qDeleteAll(m_collections);
            m_collections.clear();
            emit endResetModel();
            QJsonArray content = page["content"].toArray();
            emit layoutAboutToBeChanged();
            foreach (const QJsonValue &value, content) {
                Collection* c = new Collection(this);
                QJsonObject jsob = value.toObject();
                c->setId(jsob["id"].toString());
                c->setName(jsob["name"].toString());
                c->setOrdered(jsob["ordered"].toBool());
                c->setFiltered(jsob["filtered"].toBool());
                QJsonArray seriesArray = jsob["seriesIds"].toArray();
                QList<QString> sIds{};
                for (QJsonValue val : seriesArray) {
                    sIds.append(val.toString());
                }
                c->setSeriesIds(sIds);
                m_collections.append(std::move(c));
            }
            emit layoutChanged();
        }
        m_currentPageNumber = pageNum;
        m_totalPageNumber = totPages;
    }
}

void CollectionModel::seriesCollectionsReceived(QJsonArray list)
{
    emit beginResetModel();
    qDeleteAll(m_collections);
    m_collections.clear();
    emit endResetModel();
    emit layoutAboutToBeChanged();
    foreach (const QJsonValue &value, list) {
        Collection* c = new Collection(this);
        QJsonObject jsob = value.toObject();
        c->setId(jsob["id"].toString());
        c->setName(jsob["name"].toString());
        c->setOrdered(jsob["ordered"].toBool());
        c->setFiltered(jsob["filtered"].toBool());
        QJsonArray seriesArray = jsob["seriesIds"].toArray();
        QList<QString> sIds{};
        for (QJsonValue val : seriesArray) {
            sIds.append(val.toString());
        }
        c->setSeriesIds(sIds);
        m_collections.append(std::move(c));
    }
    emit layoutChanged();
}
