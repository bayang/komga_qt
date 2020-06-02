#include "searchmodel.h"
#include <QDateTime>
#include <QJsonArray>

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
        qDebug() << "invalid indx " << index.row();
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_results.count())
        return QVariant();

    const SearchResult* result = m_results[index.row()];
    if (role == NameRole)
        return result->name();
    else if (role == IdRole)
        return result->id();
    else if (role == ResultTypeRole)
        return result->resultType();
    return QVariant();
}
QHash<int, QByteArray> SearchModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "resultId";
        roles[NameRole] = "resultName";
        roles[ResultTypeRole] = "resultType";
        return roles;
}

void SearchModel::doSearch(const QString &searchTerm)
{
    m_api->doSearch(searchTerm, QDateTime::currentMSecsSinceEpoch());
}

qlonglong SearchModel::currentTimestamp() const
{
    qDebug() << "curr " << m_currentTimestamp;
    return m_currentTimestamp;
}

void SearchModel::setCurrentTimestamp(qlonglong currentTimestamp)
{
    qDebug() << "set b " << m_currentTimestamp;
    m_currentTimestamp = currentTimestamp;
    qDebug() << "set a " << m_currentTimestamp;
}

void SearchModel::searchBookDataReceived(QPair<QString, QJsonDocument> res)
{
    qDebug() << "search book received " << res.first << " " << res.second;
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
            Book* b = new Book(this);
            sr->setId(jsob["id"].toInt());
            sr->setName(jsob["name"].toString());
            sr->setResultType(SearchResult::ResultType::BookType);
            b->setId(jsob["id"].toInt());
            b->setSeriesId(jsob["seriesId"].toInt());
            b->setName(jsob["name"].toString());
            b->setUrl(jsob["url"].toString());
            b->setSizeBytes(jsob["sizeBytes"].toInt());
            b->setSize(jsob["size"].toString());
            QJsonObject media = jsob["media"].toObject();
            b->setMediaStatus(media["status"].toString());
            b->setPagesCount(media["pagesCount"].toInt());
            b->setMediaType(media["mediaType"].toString());
            BookMetadata* meta = new BookMetadata();
            QJsonObject metadata = jsob["metadata"].toObject();
            meta->setTitle(metadata["title"].toString());
            meta->setSummary(metadata["summary"].toString());
            meta->setNumber(metadata["number"].toString());
            meta->setNumberSort(metadata["numberSort"].toInt());
            meta->setPublisher(metadata["publisher"].toString());
            meta->setAgeRating(metadata["ageRating"].toString());
            meta->setReleaseDate(metadata["releaseDate"].toString());
            QJsonArray authors = metadata["authors"].toArray();
            QList<QString> aut{""};
            foreach (const QJsonValue &value, authors) {
                aut.append(value.toString());
            }
            meta->setAuthors(aut);
            b->setBookMetadata(meta);
            sr->setBook(std::move(b));
            m_results.append(std::move(sr));
        }
        emit endInsertRows();
    }
}

void SearchModel::searchSeriesDataReceived(QPair<QString, QJsonDocument> res)
{
    qDebug() << "search series received " << res.first << " " << res.second;
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
            Series* s = new Series(this);
            qDebug() << jsob["id"].toInt();
            qDebug() << jsob["name"].toString();
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
    qDebug() << "reset model ";
//    emit beginResetModel();
    emit beginRemoveRows(QModelIndex(), 0, m_results.size() - 1);
    qDeleteAll(m_results);
    m_results.clear();
//    emit endResetModel();
    emit endRemoveRows();
}
