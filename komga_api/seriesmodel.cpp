#include "seriesmodel.h"
#include <QJsonArray>


SeriesModel::SeriesModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}
{
    m_filters = new SeriesFilter(this);
    connect(m_api, &Komga_api::seriesDataReady,
            this, &SeriesModel::apiDataReceived);
    connect(m_api, &Komga_api::tagsDataReady,
            this, &SeriesModel::tagsDataReceived);
    connect(m_api, &Komga_api::genresDataReady,
            this, &SeriesModel::genresDataReceived);
    connect(m_api, &Komga_api::ageRatingsDataReady,
            this, &SeriesModel::ageRatingsDataReceived);
    connect(m_api, &Komga_api::languagesDataReady,
            this, &SeriesModel::languagesDataReceived);
    connect(m_api, &Komga_api::publishersDataReady,
            this, &SeriesModel::publishersDataReceived);
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
        else if (role == MetadataTagsListRole) {
            QVariantList l;
            for (auto val : series->metadataTags()) {
                l.append(val);
            }
            return l;
        }
        else if (role == MetadataGenresListRole) {
            QVariantList l;
            for (auto val : series->metadataGenres()) {
                l.append(val);
            }
            return l;
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
        roles[MetadataTagsListRole] = "seriesMetadataTagsList";
        roles[MetadataGenresListRole] = "seriesMetadataGenresList";
        return roles;
}
void SeriesModel::loadSeries(QString library) {
    m_api->getSeries(library, m_filters);
    m_api->getTags(QHash<QString,QString>{});
    m_api->getGenres(QHash<QString,QString>{});
    m_api->getAgeRatings(QHash<QString,QString>{});
    m_api->getLanguages(QHash<QString,QString>{});
    m_api->getPublishers(QHash<QString,QString>{});
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

void SeriesModel::addStatusFilter(QString status)
{
    qDebug() << "add status filter " << status;
    m_filters->addStatus(status);
}

void SeriesModel::removeStatusFilter(QString status)
{
    qDebug() << "remove status filter " << status;
    m_filters->removeStatus(status);
}

void SeriesModel::addReadStatusFilter(QString status)
{
    qDebug() << "add read status filter " << status;
    m_filters->addReadStatus(status);
}

void SeriesModel::removeReadStatusFilter(QString status)
{
    qDebug() << "remove read status filter " << status;
    m_filters->removeReadStatus(status);
}

void SeriesModel::addTagFilter(QString tag)
{
    m_filters->addTagFilter(tag);
}

void SeriesModel::removeTagFilter(QString tag)
{
    m_filters->removeTagFilter(tag);
}

void SeriesModel::addGenreFilter(QString genre)
{
    m_filters->addGenreFilter(genre);
}

void SeriesModel::removeGenreFilter(QString genre)
{
    m_filters->removeGenreFilter(genre);
}

void SeriesModel::addAgeRatingFilter(QString rating)
{
    m_filters->addAgeRatingFilter(rating);
}

void SeriesModel::removeAgeRatingFilter(QString rating)
{
    m_filters->removeAgeRatingFilter(rating);
}

void SeriesModel::addLanguageFilter(QString language)
{
    m_filters->addLanguageFilter(language);
}

void SeriesModel::removeLanguageFilter(QString language)
{
    m_filters->removeLanguageFilter(language);
}

void SeriesModel::addPublisherFilter(QString publisher)
{
    m_filters->addPublisherFilter(publisher);
}

void SeriesModel::removePublisherFilter(QString publisher)
{
    m_filters->removePublisherFilter(publisher);
}

SeriesFilter *SeriesModel::getFilters() const
{
    return m_filters;
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
        m_api->getSeries(libraryId, m_filters, m_currentPageNumber + 1);
    }
}
void SeriesModel::nextCollectionsSeriesPage(QString collectionId) {
    qDebug() << "current p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getCollectionSeries(collectionId, m_currentPageNumber + 1);
    }
}

void SeriesModel::tagsDataReceived(QList<QString> tags)
{
    qDebug() << "received tags " << tags;
    QVariantList l{};
    for (auto t : tags){
        l.append(t);
    }
    m_filters->setFilterTags(l);
}

void SeriesModel::genresDataReceived(QList<QString> genres)
{
    qDebug() << "received genres " << genres;
    QVariantList l{};
    for (auto t : genres){
        l.append(t);
    }
    m_filters->setFilterGenres(l);
}

void SeriesModel::ageRatingsDataReceived(QList<QString> ratings)
{
    qDebug() << "received ratings " << ratings;
    QVariantList l{};
    for (auto t : ratings){
        l.append(t);
    }
    m_filters->setFilterAgeRatings(l);
}

void SeriesModel::languagesDataReceived(QList<QString> languages)
{
    qDebug() << "received languages " << languages;
    QVariantList l{};
    for (auto t : languages){
        l.append(t);
    }
    m_filters->setFilterLanguages(l);
}

void SeriesModel::publishersDataReceived(QList<QString> publishers)
{
    qDebug() << "received publishers " << publishers;
    QVariantList l{};
    for (auto t : publishers){
        l.append(t);
    }
    m_filters->setFilterPublishers(l);
}

Series* SeriesModel::find(int libraryId) {
    auto itr = std::find_if(m_series.begin(), m_series.end(), [libraryId](Series* series) { return series->libraryId() == libraryId; });
    if(itr != m_series.end()) {
        return *itr;
    }
    return nullptr;
}
