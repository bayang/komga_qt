#include "seriesmodel.h"

SeriesModel::SeriesModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}
{
    connect(m_api, &Komga_api::seriesDataReady,
            this, &SeriesModel::apiDataReceived);
}
int SeriesModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_series.count();
}
QVariant SeriesModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_series.count())
        return QVariant();

    const Series* series = m_series[index.row()];
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
void SeriesModel::loadSeries(int libraryId) {
    m_api->getSeries(libraryId);
}
void SeriesModel::apiDataReceived(QList<Series*> series) {
    beginResetModel();
    m_series = series;
    endResetModel();
}
Series* SeriesModel::get(int index) {
    return m_series.at(index);
}
QByteArray SeriesModel::getThumbnail(int id) {
    QByteArray a = m_api->getThumbnail(id, Komga_api::ThumbnailType::SeriesThumbnail);
    return a;
}
