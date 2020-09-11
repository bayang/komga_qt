#include "seriesmodel.h"
#include <QJsonArray>

SeriesModel::SeriesModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}
{
    connect(m_api, &Komga_api::seriesDataReady,
            this, &SeriesModel::apiDataReceived);
}
int SeriesModel::rowCount(const QModelIndex &parent) const {
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid()) {
        return 0;
    }
    return m_series.count();
}
QVariant SeriesModel::data(const QModelIndex &index, int role) const {
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));
    if (! index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_series.count())
        return QVariant();

    const Series* series = m_series[index.row()];
    if (series) {
        if (role == NameRole) {
            return series->name();
        }
        else if (role == IdRole) {
            return series->id();
        }
        else if (role == LibraryIdRole) {
            return series->libraryId();
        }
        else if (role == BookCountRole) {
            return series->booksCount();
        }
        else if (role == UrlRole) {
            return series->url();
        }
        else if (role == MetadataStatusRole){
            return series->metadataStatus();
        }
        else if (role == BookReadCountRole) {
            return series->booksReadCount();
        }
        else if (role == BookUnreadCountRole) {
            return series->booksUnreadCount();
        }
        else if (role == BookInProgressCountRole) {
            return series->booksInProgressCount();
        }
        else if (role == MetadataSummaryRole) {
            return series->metadataSummary();
        }
        else if (role == MetadataReadingDirectionRole) {
            return series->metadataReadingDirection();
        }
        else if (role == MetadataPublisherRole) {
            return series->metadataPublisher();
        }
        else if (role == MetadataAgeRatingRole) {
            return series->metadataAgeRating();
        }
        else if (role == MetadataLanguageRole) {
            return series->metadataLanguage();
        }
        else if (role == MetadataGenresRole) {
            series->metadataGenres().join(",");
            return series->metadataGenres().join(",");
        }
        else if (role == MetadataTagsRole) {
            return series->metadataTags().join(",");
        }
    }
    return QVariant();
}
QHash<int, QByteArray> SeriesModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "seriesId";
        roles[NameRole] = "seriesName";
        roles[LibraryIdRole] = "seriesLibraryId";
        roles[BookCountRole] = "seriesBookCount";
        roles[BookReadCountRole] = "seriesBookReadCount";
        roles[BookUnreadCountRole] = "seriesBookUnreadCount";
        roles[BookInProgressCountRole] = "seriesBookInProgressCount";
        roles[UrlRole] = "seriesUrl";
        roles[MetadataStatusRole] = "seriesMetadataStatus";
        roles[MetadataSummaryRole] = "seriesMetadataSummary";
        roles[MetadataReadingDirectionRole] = "seriesMetadataReadingDirection";
        roles[MetadataPublisherRole] = "seriesMetadataPublisher";
        roles[MetadataAgeRatingRole] = "seriesMetadataAgeRating";
        roles[MetadataLanguageRole] = "seriesMetadataLanguage";
        roles[MetadataGenresRole] = "seriesMetadataGenres";
        roles[MetadataTagsRole] = "seriesMetadataTags";
        return roles;
}
void SeriesModel::loadSeries(QString library) {
    m_api->getSeries(library);
    resetSeries();
}

void SeriesModel::loadCollectionSeries(QString collectionId)
{
    m_api->getCollectionSeries(collectionId);
    resetSeries();
}

void SeriesModel::loadSeriesCollections(QString seriesId)
{
    m_api->getSeriesCollections(seriesId);
}
void SeriesModel::resetSeries() {
    emit beginRemoveRows(QModelIndex(), 0, m_series.size() - 1);
    qDeleteAll(m_series);
    m_series.clear();
    emit endRemoveRows();
}

//Series* SeriesModel::parseSeries(const QJsonValue &value) {
//    Series* s = new Series(this);
//    QJsonObject jsob = value.toObject();
//    s->setId(jsob["id"].toString());
//    QString n = jsob["name"].toString();
//    s->setName(n);
//    s->setBooksCount(jsob["booksCount"].toInt());
//    s->setBooksReadCount(jsob["booksReadCount"].toInt());
//    s->setBooksUnreadCount(jsob["booksUnreadCount"].toInt());
//    s->setBooksInProgressCount(jsob["booksInProgressCount"].toInt());
//    s->setLibraryId(jsob["libraryId"].toString());
//    QString u = jsob["url"].toString();
//    s->setUrl(u);
//    QJsonObject metadata = jsob["metadata"].toObject();
//    s->setMetadataTitle(metadata["title"].toString());
//    s->setMetadataStatus(metadata["status"].toString());
//    return s;
//}
Series *SeriesModel::parseSeries(const QJsonValue &value, QObject *parent)
{
    Series* s = new Series(parent);
    QJsonObject jsob = value.toObject();
    s->setId(jsob["id"].toString());
    QString n = jsob["name"].toString();
    s->setName(n);
    s->setBooksCount(jsob["booksCount"].toInt());
    s->setBooksReadCount(jsob["booksReadCount"].toInt());
    s->setBooksUnreadCount(jsob["booksUnreadCount"].toInt());
    s->setBooksInProgressCount(jsob["booksInProgressCount"].toInt());
    s->setLibraryId(jsob["libraryId"].toString());
    QString u = jsob["url"].toString();
    s->setUrl(u);
    QJsonObject metadata = jsob["metadata"].toObject();
    s->setMetadataTitle(metadata["title"].toString());
    s->setMetadataStatus(metadata["status"].toString());
    s->setMetadataSummary(metadata["summary"].toString());
    s->setMetadataReadingDirection(metadata["readingDirection"].toString());
    s->setMetadataPublisher(metadata["publisher"].toString());
    s->setMetadataAgeRating(metadata["ageRating"].toString());
    s->setMetadataLanguage(metadata["language"].toString());
    s->setMetadataCreated(metadata["created"].toString());
    s->setMetadataLastModified(metadata["lastModified"].toString());
    QJsonArray genresArray = metadata["genres"].toArray();
    QList<QString> genres{};
    foreach (const QJsonValue &val, genresArray) {
        genres.append(val.toString());
    }
    s->setMetadataGenres(genres);
    QJsonArray tagsArray = metadata["tags"].toArray();
    QList<QString> tags{};
    foreach (const QJsonValue &val, tagsArray) {
        tags.append(val.toString());
    }
    s->setMetadataTags(tags);
    return s;
}

void SeriesModel::apiDataReceived(QJsonObject page) {
    int pageNum = page["number"].toInt();
    int totPages = page["totalPages"].toInt();
    int nbElems = page["numberOfElements"].toInt();
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_series.size(), m_series.size() + nbElems - 1);
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                m_series.append(std::move(parseSeries(value, this)));
            }
            emit endInsertRows();
        }
        else {
            QList<Series*> series{};
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                series.append(std::move(parseSeries(value, this)));

            }

            emit layoutAboutToBeChanged();
            m_series = series;
            changePersistentIndex(index(0), QModelIndex());
            emit layoutChanged();
        }
        m_currentPageNumber = pageNum;
        m_totalPageNumber = totPages;
    }
}

void SeriesModel::updateProgress(QString seriesId, bool completed)
{
    m_api->updateSeriesProgress(seriesId, completed);
}
QByteArray SeriesModel::getThumbnail(int id) {
    QByteArray a = m_api->getThumbnail(id, Komga_api::ThumbnailType::SeriesThumbnail);
    return a;
}
void SeriesModel::nextSeriesPage(QString libraryId) {
    qDebug() << "current p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getSeries(libraryId, m_currentPageNumber + 1);
    }
}
void SeriesModel::nextCollectionsSeriesPage(QString collectionId) {
    qDebug() << "current p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getCollectionSeries(collectionId, m_currentPageNumber + 1);
    }
}

Series* SeriesModel::find(int libraryId) {
    auto itr = std::find_if(m_series.begin(), m_series.end(), [libraryId](Series* series) { return series->libraryId() == libraryId; });
    if(itr != m_series.end()) {
        return *itr;
    }
    return nullptr;
}
