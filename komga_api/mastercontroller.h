#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QSortFilterProxyModel>
#include "komga_api_global.h"
#include "seriesfiltersortproxymodel.h"
#include "library.h"
#include "series.h"
#include "book.h"
#include "bookmodel.h"
#include "librarymodel.h"
#include "seriesmodel.h"
#include "searchmodel.h"
#include "collectionmodel.h"
#include "networkinformer.h"

class KOMGA_API_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( SeriesModel* ui_seriesModel READ getSeriesModel CONSTANT )
    Q_PROPERTY( BookModel* ui_bookModel READ getBookModel CONSTANT )
    Q_PROPERTY( LibraryModel* ui_libraryModel READ getLibraryModel CONSTANT )
    Q_PROPERTY( SearchModel* ui_searchModel READ getSearchModel CONSTANT )
    Q_PROPERTY( CollectionModel* ui_collectionModel READ getCollectionModel CONSTANT )
    Q_PROPERTY( QString ui_defaultLibraryId MEMBER DEFAULT_LIBRARY_ID CONSTANT )
    Q_PROPERTY( QString ui_newSeriesId MEMBER SERIES_NEW_ID CONSTANT )
    Q_PROPERTY( QString ui_latestSeriesId MEMBER SERIES_LATEST_ID CONSTANT )
    Q_PROPERTY( QString ui_updatedSeriesId MEMBER SERIES_UPDATED_ID CONSTANT )
    Q_PROPERTY( QString ui_newSeriesName MEMBER SERIES_NEW_NAME CONSTANT )
    Q_PROPERTY( QString ui_latestSeriesName MEMBER SERIES_LATEST_NAME CONSTANT )
    Q_PROPERTY( QString ui_updatedSeriesName MEMBER SERIES_UPDATED_NAME CONSTANT )
    Q_PROPERTY( QString ui_defaultLibraryName MEMBER DEFAULT_LIBRARY_NAME CONSTANT )
    Q_PROPERTY( QString ui_latestBooksName MEMBER BOOKS_LATEST_NAME CONSTANT )
    Q_PROPERTY( QString ui_latestBooksId MEMBER BOOKS_LATEST_ID CONSTANT )
    Q_PROPERTY( QString ui_ondeckBooksName MEMBER BOOKS_ON_DECK_NAME CONSTANT )
    Q_PROPERTY( QString ui_ondeckBooksId MEMBER BOOKS_ON_DECK_ID CONSTANT )
    Q_PROPERTY( QString ui_collectionsId MEMBER COLLECTIONS_ID CONSTANT )
    Q_PROPERTY( QString ui_collectionsName MEMBER COLLECTIONS_NAME CONSTANT )
    Q_PROPERTY( QString ui_readingBooksName MEMBER BOOKS_READING_NAME CONSTANT )
    Q_PROPERTY( QString ui_readingBooksId MEMBER BOOKS_READING_ID CONSTANT )
    Q_PROPERTY( NetworkInformer* ui_networkInformer READ getNetworkInformer CONSTANT )

public:
    explicit MasterController(SeriesModel *seriesModel, BookModel *bookModel, CollectionModel *collectionModel, NetworkInformer *informer, QObject *parent = nullptr);

    static const QString DEFAULT_LIBRARY_ID;
    static const QString SERIES_NEW_ID;
    static const QString SERIES_LATEST_ID;
    static const QString SERIES_UPDATED_ID;

    static const QString DEFAULT_LIBRARY_NAME;

    static const QString SERIES_UPDATED_NAME;
    static const QString SERIES_NEW_NAME;
    static const QString SERIES_LATEST_NAME;

    static const QString BOOKS_LATEST_ID;
    static const QString BOOKS_LATEST_NAME;
    static const QString BOOKS_READING_ID;
    static const QString BOOKS_READING_NAME;
    static const QString BOOKS_ON_DECK_ID;
    static const QString BOOKS_ON_DECK_NAME;

    static const QString COLLECTIONS_ID;
    static const QString COLLECTIONS_NAME;

    LibraryModel *getLibraryModel() const;

    SeriesModel *getSeriesModel() const;

    BookModel *getBookModel() const;

    SeriesFilterSortProxyModel *getProxyModel() const;

    int getSelectedBookIdx() const;

    NetworkInformer *getNetworkInformer() const;

    SearchModel *getSearchModel() const;

    void setLibraryModel(LibraryModel *libraryModel);
    void setSearchModel(SearchModel *searchModel);

    CollectionModel *getCollectionModel() const;
    void setCollectionModel(CollectionModel *collectionModel);

signals:
    void loadSeriesView(QString seriesId);
    void loadCollectionSeriesView(QString collectionId);
    void loadSeriesCollections(QString seriesId);
    void loadBooksView(QString seriesId);
    void loadCollectionsView();

public slots:
    void nextSeriesPage(QString currentLibraryId);
    void nextBooksPage(QString currentSeriesId);
    void nextCollectionsPage();
    void nextCollectionsSeriesPage(QString currentCollectionId);
    void setSelectedBookIdx(int value);
    void refreshData();
    void doSearch(const QString &searchTerm);
    void resetSearch();
    void setCurrentBookPageReached(int currentImageNumber);
    void preloadBookPages(QString bookId, int currentPage, int pageCount);
    void updateprogress(QString bookId, int currentPage);
    void markRead(QModelIndexList list, QString type, bool completed = true);

private:
    LibraryModel* m_libraryModel{nullptr};
    SeriesModel* m_seriesModel{nullptr};
    BookModel* m_bookModel{nullptr};
    SearchModel* m_searchModel{nullptr};
    CollectionModel* m_collectionModel{nullptr};
    int m_currentImageNumber{0};
    int selectedBookIdx{-1};
    NetworkInformer* m_networkInformer{nullptr};

};

#endif // MASTERCONTROLLER_H
