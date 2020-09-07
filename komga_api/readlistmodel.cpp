#include "readlistmodel.h"
#include <QJsonArray>

ReadListModel::ReadListModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}
{
    connect(m_api, &Komga_api::readListsDataReady,
            this, &ReadListModel::apiDataReceived);
}

void ReadListModel::loadReadLists()
{
    qDebug() << "load read lists";
    m_api->getReadLists();
}

int ReadListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_readLists.count();
}

QVariant ReadListModel::data(const QModelIndex &index, int role) const
{
    if (! index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_readLists.count())
        return QVariant();

    const ReadList* readList = m_readLists[index.row()];
    if (role == IdRole) {
        return readList->id();
    }
    else if (role == NameRole) {
        return readList->name();
    }
    else if (role == BooksIdsRole) {
        return QVariant::fromValue(readList->booksIds());
    }
    else if (role == FilteredRole) {
        return readList->filtered();
    }
    else if (role == SizeRole) {
        return readList->booksIds().count();
    }
    return QVariant();
}

QHash<int, QByteArray> ReadListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[IdRole] = "readListId";
        roles[NameRole] = "readListName";
        roles[BooksIdsRole] = "readListBooksId";
        roles[FilteredRole] = "readListFiltered";
        roles[SizeRole] = "readListSize";
        return roles;
}

void ReadListModel::apiDataReceived(QJsonObject page)
{
    qDebug() << "received readlists " << page;
    int pageNum = page["number"].toInt();
    int totPages = page["totalPages"].toInt();
    int nbElems = page["numberOfElements"].toInt();
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_readLists.size(), m_readLists.size() + nbElems - 1);
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                ReadList* r = new ReadList(this);
                QJsonObject jsob = value.toObject();
                r->setId(jsob["id"].toString());
                r->setName(jsob["name"].toString());
                r->setFiltered(jsob["filtered"].toBool());
                QJsonArray booksArray = jsob["bookIds"].toArray();
                foreach (const QJsonValue &val, booksArray) {
                    r->booksIds().append(val.toString());
                }
                m_readLists.append(std::move(r));
            }
            emit endInsertRows();
        }
        else {
            emit beginResetModel();
            qDeleteAll(m_readLists);
            m_readLists.clear();
            emit endResetModel();
            QJsonArray content = page["content"].toArray();
            emit layoutAboutToBeChanged();
            foreach (const QJsonValue &value, content) {
                ReadList* r = new ReadList(this);
                QJsonObject jsob = value.toObject();
                r->setId(jsob["id"].toString());
                r->setName(jsob["name"].toString());
                r->setFiltered(jsob["filtered"].toBool());
                QJsonArray booksArray = jsob["bookIds"].toArray();
                QList<QString> bIds{};
                foreach (const QJsonValue &val, booksArray) {
                    bIds.append(val.toString());
                }
                r->setBooksIds(bIds);
                m_readLists.append(std::move(r));
            }
            emit layoutChanged();
        }
        m_currentPageNumber = pageNum;
        m_totalPageNumber = totPages;
    }
}

void ReadListModel::nextReadListsPage()
{
    qDebug() << "curr p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getReadLists(m_currentPageNumber + 1);
    }
}

