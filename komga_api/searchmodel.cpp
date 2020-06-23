#include "searchmodel.h"
#include <QDateTime>
#include <QJsonArray>
#include <QMetaEnum>
#include "bookmodel.h"

SearchModel::SearchModel(QObject *parent, Komga_api* api) :
   QAbstractListModel{parent}, m_api{api}, m_results{}
{
    connect(m_api, &Komga_api::searchBookDataReady,
            this, &SearchModel::searchBookDataReceived);
    connect(m_api, &Komga_api::searchSeriesDataReady,
            this, &SearchModel::searchSeriesDataReceived);

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
        return QString("Series");
    }
    else if (role == SeriesRole){
        return QVariant::fromValue(result->series());
    }
    else if (role == BookRole){
        return QVariant::fromValue(result->book());
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
    if (nbElems > 0) {
        qlonglong n = res.first.section('/', 0, 0).toLongLong();
        // new search result, clear previous data
        if (n > currentTimestamp()) {
            resetModel();
            setCurrentTimestamp(n);
        }
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
            Series* s = new Series(this);
            QString n = jsob["name"].toString();
            sr->setId(jsob["id"].toInt());
            sr->setName(n);
            sr->setResultType(SearchResult::ResultType::SeriesType);
            s->setId(jsob["id"].toInt());
            s->setName(n);
            s->setBooksCount(jsob["booksCount"].toInt());
            s->setLibraryId(jsob["libraryId"].toInt());
            QString u = jsob["url"].toString();
            s->setUrl(u);
            QJsonObject metadata = jsob["metadata"].toObject();
            s->setMetadataTitle(metadata["title"].toString());
            s->setMetadataStatus(metadata["status"].toString());
            sr->setSeries(std::move(s));
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
