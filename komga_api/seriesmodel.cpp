#include "seriesmodel.h"
#include <QJsonArray>

SeriesModel::SeriesModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}
{
    connect(m_api, &Komga_api::seriesDataReady,
            this, &SeriesModel::apiDataReceived);
}
int SeriesModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_series.count();
}
QVariant SeriesModel::data(const QModelIndex &index, int role) const {
    if (! index.isValid()) {
        qDebug() << "invalid indx " << index.row();
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_series.count())
        return QVariant();

    const Series* series = m_series[index.row()];
    if (series) {
        if (role == NameRole)
            return series->name();
        else if (role == IdRole)
            return series->id();
        else if (role == LibraryIdRole)
            return series->libraryId();
        else if (role == BookCountRole)
            return series->booksCount();
        else if (role == UrlRole)
            return series->url();
    }
    return QVariant();
}
QHash<int, QByteArray> SeriesModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "seriesId";
        roles[NameRole] = "seriesName";
        roles[LibraryIdRole] = "seriesLibraryId";
        roles[BookCountRole] = "seriesBookCount";
        roles[UrlRole] = "seriesUrl";
        return roles;
}
void SeriesModel::loadSeries(Library* library) {
    m_api->getSeries(library->id());
}

void SeriesModel::apiDataReceived(QJsonObject page) {
    int pageNum = page["number"].toInt();
    int totPages = page["totalPages"].toInt();
    int nbElems = page["numberOfElements"].toInt();
    qDebug() << "page : " << pageNum;
    qDebug() << "page number : " << totPages;
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_series.size(), m_series.size() + nbElems - 1);
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                Series* s = new Series(this);
                QJsonObject jsob = value.toObject();
                qDebug() << jsob["id"].toInt();
                qDebug() << jsob["name"].toString();
                s->setId(jsob["id"].toInt());
                QString n = jsob["name"].toString();
                s->setName(n);
                s->setBooksCount(jsob["booksCount"].toInt());
                s->setLibraryId(jsob["libraryId"].toInt());
                QString u = jsob["url"].toString();
                s->setUrl(u);
                QJsonObject metadata = jsob["metadata"].toObject();
                s->setMetadataTitle(metadata["title"].toString());
                s->setMetadataStatus(metadata["status"].toString());
                m_series.append(std::move(s));
            }
            emit endInsertRows();
        }
        else {
    //        emit beginResetModel();
            emit layoutAboutToBeChanged();
            qDeleteAll(m_series);
            m_series.clear();
    //        QList<Series*> series{};
            QJsonArray content = page["content"].toArray();
            foreach (const QJsonValue &value, content) {
                Series* s = new Series(this);
                QJsonObject jsob = value.toObject();
                qDebug() << jsob["id"].toInt();
                qDebug() << jsob["name"].toString();
                s->setId(jsob["id"].toInt());
                QString n = jsob["name"].toString();
                s->setName(n);
                s->setBooksCount(jsob["booksCount"].toInt());
                s->setLibraryId(jsob["libraryId"].toInt());
                QString u = jsob["url"].toString();
                s->setUrl(u);
                QJsonObject metadata = jsob["metadata"].toObject();
                s->setMetadataTitle(metadata["title"].toString());
                s->setMetadataStatus(metadata["status"].toString());
                m_series.append(std::move(s));
            }
    //        m_series = series;
    //        emit endResetModel();
            changePersistentIndex(index(0), QModelIndex());
            emit layoutChanged();
        }
        m_currentPageNumber = pageNum;
        m_totalPageNumber = totPages;
    }
}
Series* SeriesModel::get(int index) {
    return m_series.at(index);
}
QByteArray SeriesModel::getThumbnail(int id) {
    QByteArray a = m_api->getThumbnail(id, Komga_api::ThumbnailType::SeriesThumbnail);
    return a;
}
void SeriesModel::nextSeriesPage(Library *library) {
    qDebug() << "curr p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getSeries(library->id(), m_currentPageNumber + 1);
    }
}
Series* SeriesModel::find(int libraryId) {
    auto itr = std::find_if(m_series.begin(), m_series.end(), [libraryId](Series* series) { return series->libraryId() == libraryId; });
    if(itr != m_series.end()) {
        qDebug() << "find " << (*itr)->name();
        return *itr;
    }
    return nullptr;
}
