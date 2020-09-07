#include "searchmodel.h"
#include <QDateTime>
#include <QJsonArray>
#include <QMetaEnum>
#include "bookmodel.h"
#include "seriesmodel.h"
#include "collection.h"
#include "readlist.h"

SearchModel::SearchModel(QObject *parent, Komga_api* api) :
   QAbstractListModel{parent}, m_api{api}, m_results{}
{
    connect(m_api, &Komga_api::searchBookDataReady,
            this, &SearchModel::searchBookDataReceived);
    connect(m_api, &Komga_api::searchSeriesDataReady,
            this, &SearchModel::searchSeriesDataReceived);
    connect(m_api, &Komga_api::searchCollectionsDataReady,
            this, &SearchModel::searchCollectionsDataReceived);
    connect(m_api, &Komga_api::searchReadListsDataReady,
            this, &SearchModel::searchReadListsDataReceived);
}
int SearchModel::rowCount(const QModelIndex &parent) const {
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid()) {
        return 0;
    }
    return m_results.count();
}
QVariant SearchModel::data(const QModelIndex &index, int role) const {
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));
    if (! index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_results.count())
        return QVariant();

    const SearchResult* result = m_results[index.row()];
    if (role == NameRole)
        return result->name();
    else if (role == IdRole)
        return result->id();
    else if (role == ResultTypeRole) {
        if (result->resultType() == SearchResult::ResultType::BookType) {
            return QString("Books");
        }
        else if (result->resultType() == SearchResult::ResultType::CollectionType) {
            return QString("Collections");
        }
        else if (result->resultType() == SearchResult::ResultType::ReadListType) {
            return QString("Readlist");
        }
        return QString("Series");
    }
    else if (role == SeriesRole){
        return QVariant::fromValue(result->series());
    }
    else if (role == BookRole){
        return QVariant::fromValue(result->book());
    }
    else if (role == CollectionRole){
        return QVariant::fromValue(result->collection());
    }
    else if (role == ReadListRole){
        return QVariant::fromValue(result->readList());
    }
    return QVariant();
}
QHash<int, QByteArray> SearchModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "resultId";
        roles[NameRole] = "resultName";
        roles[ResultTypeRole] = "resultType";
        roles[SeriesRole] = "resultSeries";
        roles[BookRole] = "resultBook";
        roles[CollectionRole] = "resultCollection";
        roles[ReadListRole] = "resultReadList";
        return roles;
}

void SearchModel::doSearch(const QString &searchTerm)
{
    m_api->doSearch(searchTerm, QDateTime::currentMSecsSinceEpoch());
}

qlonglong SearchModel::currentTimestamp() const
{
    return m_currentTimestamp;
}

void SearchModel::setCurrentTimestamp(qlonglong currentTimestamp)
{
    m_currentTimestamp = currentTimestamp;
}

SearchResult *SearchModel::at(int index)
{
    return m_results.at(index);
}

void SearchModel::searchBookDataReceived(QPair<QString, QJsonDocument> res)
{
    QJsonObject page = res.second.object();
    int nbElems = page["numberOfElements"].toInt();
    qlonglong n = res.first.section('/', 0, 0).toLongLong();
    // new search result, clear previous data
    if (n > currentTimestamp()) {
        resetModel();
        setCurrentTimestamp(n);
    }
    if (nbElems > 0) {
        emit beginInsertRows(QModelIndex(), m_results.size(), m_results.size() + nbElems - 1);
        QJsonArray content = page["content"].toArray();
        foreach (const QJsonValue &value, content) {
            QJsonObject jsob = value.toObject();
            SearchResult* sr = new SearchResult(this);
            sr->setResultType(SearchResult::ResultType::BookType);
            Book* parsed = BookModel::parseBook(value, sr);
            sr->setId(parsed->id());
            sr->setName(parsed->name());
            sr->setBook(parsed);
            m_results.append(std::move(sr));
        }
        emit endInsertRows();
    }
}

void SearchModel::searchSeriesDataReceived(QPair<QString, QJsonDocument> res)
{
    QJsonObject page = res.second.object();
    int nbElems = page["numberOfElements"].toInt();
    qlonglong n = res.first.section('/', 0, 0).toLongLong();
    // new search result, clear previous data
    if (n > currentTimestamp()) {
        resetModel();
        setCurrentTimestamp(n);
    }
    if (nbElems > 0) {
        emit beginInsertRows(QModelIndex(), m_results.size(), m_results.size() + nbElems - 1);
        QJsonArray content = page["content"].toArray();
        foreach (const QJsonValue &value, content) {
            QJsonObject jsob = value.toObject();
            SearchResult* sr = new SearchResult(this);
//            Series* s = new Series(this);
            Series* s = SeriesModel::parseSeries(value, sr);
            QString n = jsob["name"].toString();
            sr->setId(jsob["id"].toString());
            sr->setName(n);
            sr->setResultType(SearchResult::ResultType::SeriesType);
//            s->setId(jsob["id"].toString());
//            s->setName(n);
//            s->setBooksCount(jsob["booksCount"].toInt());
//            s->setLibraryId(jsob["libraryId"].toString());
//            QString u = jsob["url"].toString();
//            s->setUrl(u);
//            QJsonObject metadata = jsob["metadata"].toObject();
//            s->setMetadataTitle(metadata["title"].toString());
//            s->setMetadataStatus(metadata["status"].toString());
            sr->setSeries(std::move(s));
            m_results.append(std::move(sr));
        }
        emit endInsertRows();
    }
}

void SearchModel::searchCollectionsDataReceived(QPair<QString, QJsonDocument> res)
{
    QJsonObject page = res.second.object();
    int nbElems = page["numberOfElements"].toInt();
    qlonglong n = res.first.section('/', 0, 0).toLongLong();
    // new search result, clear previous data
    if (n > currentTimestamp()) {
        resetModel();
        setCurrentTimestamp(n);
    }
    if (nbElems > 0) {
        emit beginInsertRows(QModelIndex(), m_results.size(), m_results.size() + nbElems - 1);
        QJsonArray content = page["content"].toArray();
        foreach (const QJsonValue &value, content) {
            QJsonObject jsob = value.toObject();
            SearchResult* sr = new SearchResult(this);
            Collection* c = new Collection(this);
            c->setId(jsob["id"].toString());
            QString n = jsob["name"].toString();
            c->setName(n);
            c->setOrdered(jsob["ordered"].toBool());
            c->setFiltered(jsob["filtered"].toBool());
            QJsonArray seriesArray = jsob["seriesIds"].toArray();
            QList<QString> seriesIds;
            foreach (const QJsonValue &val, seriesArray) {
                seriesIds.append(val.toString());
            }
            c->setSeriesIds(seriesIds);
            sr->setId(jsob["id"].toString());
            sr->setName(n);
            sr->setResultType(SearchResult::ResultType::CollectionType);
            sr->setCollection(std::move(c));
            m_results.append(std::move(sr));
        }
        emit endInsertRows();
    }
}

void SearchModel::searchReadListsDataReceived(QPair<QString, QJsonDocument> res)
{
    QJsonObject page = res.second.object();
    int nbElems = page["numberOfElements"].toInt();
    qlonglong n = res.first.section('/', 0, 0).toLongLong();
    // new search result, clear previous data
    if (n > currentTimestamp()) {
        resetModel();
        setCurrentTimestamp(n);
    }
    if (nbElems > 0) {
        emit beginInsertRows(QModelIndex(), m_results.size(), m_results.size() + nbElems - 1);
        QJsonArray content = page["content"].toArray();
        foreach (const QJsonValue &value, content) {
            QJsonObject jsob = value.toObject();
            SearchResult* sr = new SearchResult(this);
            ReadList* r = new ReadList(this);
            r->setId(jsob["id"].toString());
            r->setName(jsob["name"].toString());
            r->setFiltered(jsob["filtered"].toBool());
            QJsonArray booksArray = jsob["bookIds"].toArray();
            QList<QString> booksIds;
            foreach (const QJsonValue &val, booksArray) {
                booksIds.append(val.toString());
            }
            r->setBooksIds(booksIds);
            sr->setId(jsob["id"].toString());
            sr->setName(jsob["name"].toString());
            sr->setResultType(SearchResult::ResultType::ReadListType);
            sr->setReadList(std::move(r));
            m_results.append(std::move(sr));
        }
        emit endInsertRows();
    }
}

void SearchModel::resetModel() {
    emit beginRemoveRows(QModelIndex(), 0, m_results.size() - 1);
    qDeleteAll(m_results);
    m_results.clear();
    emit endRemoveRows();
}
