#ifndef SERIESMODEL_H
#define SERIESMODEL_H

#include "komga_api_global.h"
#include "komga_api.h"
#include <QObject>
#include <QAbstractListModel>
#include <QJsonObject>

class KOMGA_API_EXPORT SeriesModel : public QAbstractListModel
{
    Q_OBJECT
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
    };
private slots:
    void apiDataReceived(QJsonObject series);

public slots:
    void updateProgress(QString seriesId, bool completed = true);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void loadSeries(QString library);
    Q_INVOKABLE void loadCollectionSeries(QString collectionId);
    Q_INVOKABLE void loadSeriesCollections(QString seriesId);
    void nextSeriesPage(QString libraryId);
    QByteArray getThumbnail(int id);
    Series* find(int libraryId);
    void resetSeries();
    Series *parseSeries(const QJsonValue &value);
    void nextCollectionsSeriesPage(QString collectionId);
signals:
    void refresh();

private:
    Komga_api* m_api = nullptr;
    QList<Series*> m_series{};
    int m_currentPageNumber{};
    int m_totalPageNumber{};
};



#endif // SERIESMODEL_H
