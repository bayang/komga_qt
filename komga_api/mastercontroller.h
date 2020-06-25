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
#include "networkinformer.h"

class KOMGA_API_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( SeriesModel* ui_seriesModel READ getSeriesModel CONSTANT )
    Q_PROPERTY( BookModel* ui_bookModel READ getBookModel CONSTANT )
    Q_PROPERTY( LibraryModel* ui_libraryModel READ getLibraryModel CONSTANT )
    Q_PROPERTY( SearchModel* ui_searchModel READ getSearchModel CONSTANT )
    Q_PROPERTY( int ui_defaultLibraryId MEMBER DEFAULT_LIBRARY_ID CONSTANT )
    Q_PROPERTY( int ui_newSeriesId MEMBER SERIES_NEW_ID CONSTANT )
    Q_PROPERTY( int ui_latestSeriesId MEMBER SERIES_LATEST_ID CONSTANT )
    Q_PROPERTY( int ui_updatedSeriesId MEMBER SERIES_UPDATED_ID CONSTANT )
    Q_PROPERTY( QString ui_newSeriesName MEMBER SERIES_NEW_NAME CONSTANT )
    Q_PROPERTY( QString ui_latestSeriesName MEMBER SERIES_LATEST_NAME CONSTANT )
    Q_PROPERTY( QString ui_updatedSeriesName MEMBER SERIES_UPDATED_NAME CONSTANT )
    Q_PROPERTY( QString ui_defaultLibraryName MEMBER DEFAULT_LIBRARY_NAME CONSTANT )
    Q_PROPERTY( QString ui_latestBooksName MEMBER BOOKS_LATEST_NAME CONSTANT )
    Q_PROPERTY( int ui_latestBooksId MEMBER BOOKS_LATEST_ID CONSTANT )
    Q_PROPERTY( QString ui_readingBooksName MEMBER BOOKS_READING_NAME CONSTANT )
    Q_PROPERTY( int ui_readingBooksId MEMBER BOOKS_READING_ID CONSTANT )
    Q_PROPERTY( NetworkInformer* ui_networkInformer READ getNetworkInformer CONSTANT )

public:
    explicit MasterController(SeriesModel *seriesModel, BookModel *bookModel, NetworkInformer *informer, QObject *parent = nullptr);

    static const int DEFAULT_LIBRARY_ID{-100};
    static const int SERIES_NEW_ID{-101};
    static const int SERIES_LATEST_ID{-102};
    static const int SERIES_UPDATED_ID{-103};

    static const QString DEFAULT_LIBRARY_NAME;

    static const QString SERIES_UPDATED_NAME;
    static const QString SERIES_NEW_NAME;
    static const QString SERIES_LATEST_NAME;

    static const int BOOKS_LATEST_ID{-1001};
    static const QString BOOKS_LATEST_NAME;
    static const int BOOKS_READING_ID{-1002};
    static const QString BOOKS_READING_NAME;

    static const int COLLECTIONS_ID{-2002};
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

signals:
    void loadSeriesView(int seriesId);
    void loadBooksView(int seriesId);

public slots:
    void nextSeriesPage(int currentLibraryId);
    void nextBooksPage(int currentSeriesId);
    void setSelectedBookIdx(int value);
    void refreshData();
    void doSearch(const QString &searchTerm);
    void resetSearch();
    void setCurrentBookPageReached(int currentImageNumber);
    void preloadBookPages(int bookId, int currentPage, int pageCount);
    void updateprogress(int bookId, int currentPage);

private:
    LibraryModel* m_libraryModel{nullptr};
    SeriesModel* m_seriesModel{nullptr};
    BookModel* m_bookModel{nullptr};
    SearchModel* m_searchModel{nullptr};
    int m_currentImageNumber{0};
    int selectedBookIdx{-1};
    NetworkInformer* m_networkInformer{nullptr};

};

#endif // MASTERCONTROLLER_H
