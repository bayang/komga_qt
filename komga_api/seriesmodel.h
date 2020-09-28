#ifndef SERIESMODEL_H
#define SERIESMODEL_H

#include "komga_api_global.h"
#include "komga_api.h"
#include "seriesfilter.h"
#include <QObject>
#include <QAbstractListModel>
#include <QJsonObject>

class KOMGA_API_EXPORT SeriesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( SeriesFilter* ui_seriesFilter READ getFilters CONSTANT )

public:
    SeriesModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum SeriesRoles {
        IdRole = Qt::UserRole + 1,
        LibraryIdRole = Qt::UserRole + 2,
        NameRole = Qt::UserRole + 3,
        BookCountRole = Qt::UserRole + 4,
        UrlRole = Qt::UserRole + 5,
        MetadataStatusRole = Qt::UserRole + 6,
        BookReadCountRole = Qt::UserRole + 7,
        BookUnreadCountRole = Qt::UserRole + 8,
        BookInProgressCountRole = Qt::UserRole + 9,
        MetadataSummaryRole = Qt::UserRole + 10,
        MetadataReadingDirectionRole = Qt::UserRole + 11,
        MetadataPublisherRole = Qt::UserRole + 12,
        MetadataAgeRatingRole = Qt::UserRole + 13,
        MetadataLanguageRole = Qt::UserRole + 14,
        MetadataGenresRole = Qt::UserRole + 15,
        MetadataTagsRole = Qt::UserRole + 16,
        MetadataTagsListRole = Qt::UserRole + 17,
        MetadataGenresListRole = Qt::UserRole + 18,
    };
private slots:
    void apiDataReceived(QJsonObject series);

public slots:
    void updateProgress(QString seriesId, bool completed = true);
    void tagsDataReceived(QList<QString> tags);
    void genresDataReceived(QList<QString> genres);
    void ageRatingsDataReceived(QList<QString> ratings);
    void languagesDataReceived(QList<QString> languages);
    void publishersDataReceived(QList<QString> publishers);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void loadSeries(QString library);
    Q_INVOKABLE void loadCollectionSeries(QString collectionId);
    Q_INVOKABLE void loadSeriesCollections(QString seriesId);
    Q_INVOKABLE void filterSeries(QString library);
    void nextSeriesPage(QString libraryId);
    QByteArray getThumbnail(int id);
    Series* find(int libraryId);
    void resetSeries();
    void nextCollectionsSeriesPage(QString collectionId);
    static Series *parseSeries(const QJsonValue &value, QObject* parent);
    Q_INVOKABLE void addStatusFilter(QString status);
    Q_INVOKABLE void removeStatusFilter(QString status);
    Q_INVOKABLE void addReadStatusFilter(QString status);
    Q_INVOKABLE void removeReadStatusFilter(QString status);
    Q_INVOKABLE void addTagFilter(QString tag);
    Q_INVOKABLE void removeTagFilter(QString tag);
    Q_INVOKABLE void addGenreFilter(QString genre);
    Q_INVOKABLE void removeGenreFilter(QString genre);
    Q_INVOKABLE void addAgeRatingFilter(QString rating);
    Q_INVOKABLE void removeAgeRatingFilter(QString rating);
    Q_INVOKABLE void addLanguageFilter(QString language);
    Q_INVOKABLE void removeLanguageFilter(QString language);
    Q_INVOKABLE void addPublisherFilter(QString publisher);
    Q_INVOKABLE void removePublisherFilter(QString publisher);

    SeriesFilter *getFilters() const;

signals:
    void refresh();
    void filtersApplied();

private:
    Komga_api* m_api = nullptr;
    QList<Series*> m_series{};
    int m_currentPageNumber{};
    int m_totalPageNumber{};
    SeriesFilter* m_filters;
};



#endif // SERIESMODEL_H
