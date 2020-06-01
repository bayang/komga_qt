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
    Q_PROPERTY( Book* ui_currentBook READ getCurrentBook NOTIFY currentBookChanged )
    Q_PROPERTY( Library* ui_defautLibrary READ getDefaultLibrary WRITE setDefaultLibrary NOTIFY defaultLibraryChanged )
    Q_PROPERTY( Series* ui_currentSeries READ getCurrentSeries NOTIFY currentSeriesChanged )
    Q_PROPERTY( SeriesModel* ui_seriesModel READ getSeriesModel CONSTANT )
    Q_PROPERTY( BookModel* ui_bookModel READ getBookModel CONSTANT )
    Q_PROPERTY( LibraryModel* ui_libraryModel READ getLibraryModel CONSTANT )
    Q_PROPERTY( SearchModel* ui_searchModel READ getSearchModel CONSTANT )
    Q_PROPERTY( int ui_defaultLibraryId MEMBER DEFAULT_LIBRARY_ID CONSTANT )
    Q_PROPERTY( int ui_newSeriesId MEMBER SERIES_NEW_ID CONSTANT )
    Q_PROPERTY( int ui_latestSeriesId MEMBER SERIES_LATEST_ID CONSTANT )
    Q_PROPERTY( int ui_updatedSeriesId MEMBER SERIES_UPDATED_ID CONSTANT )
    Q_PROPERTY( int ui_currPageNumber READ getCurrentImageNumber WRITE setCurrentImageNumber NOTIFY currentImageNumberChanged )
    Q_PROPERTY( QString ui_currentLibraryName READ getCurrentLibraryName NOTIFY currentLibraryNameChanged )
    Q_PROPERTY( NetworkInformer* ui_networkInformer READ getNetworkInformer CONSTANT )

public:
    explicit MasterController(SeriesModel *seriesModel, BookModel *bookModel, NetworkInformer *informer, QObject *parent = nullptr);

    static const int DEFAULT_LIBRARY_ID{-100};
    static const int SERIES_NEW_ID{-101};
    static const int SERIES_LATEST_ID{-102};
    static const int SERIES_UPDATED_ID{-103};

    static const QString SERIES_UPDATED_NAME;
    static const QString SERIES_NEW_NAME;
    static const QString SERIES_LATEST_NAME;

    Book *getCurrentBook() const;

    Series *getCurrentSeries() const;

    Library *getDefaultLibrary() const;
    void setDefaultLibrary(Library *value);

    LibraryModel *getLibraryModel() const;
    void setLibraryModel(LibraryModel *libraryModel);

    SeriesModel *getSeriesModel() const;
    void setSeriesModel(SeriesModel *seriesModel);

    BookModel *getBookModel() const;
    void setBookModel(BookModel *bookModel);


    SeriesFilterSortProxyModel *getProxyModel() const;
    void setProxyModel(SeriesFilterSortProxyModel *proxyModel);

    int getCurrentImageNumber() const;
    void setCurrentImageNumber(int currentImageNumber);

    int getSelectedSeriesIdx() const;
    void setSelectedSeriesIdx(int value);

    int getSelectedLibraryIdx() const;
    void setSelectedLibraryIdx(int value);

    int getSelectedBookIdx() const;
    void setSelectedBookIdx(int value);

    NetworkInformer *getNetworkInformer() const;
    void setNetworkInformer(NetworkInformer *networkInformer);

    SearchModel *getSearchModel() const;
    void setSearchModel(SearchModel *searchModel);

signals:
    void goSeriesView();
    void goBooksView();
    void goBookDetailView();
    void goBookReadView();
    void currentBookChanged(Book* book);
    void currentLibraryChanged(int id);
    void currentLibraryNameChanged(QString name);
    void defaultLibraryChanged();
    void currentSeriesChanged(Series *series);
    void currentImageNumberChanged(int newValue);
    void firstBookPageReached();
    void lastBookPageReached();

public slots:
    void nextSeriesPage();
    void nextBooksPage();
    void setSelectedLibrary(int selectedLibrary);
    void setSelectedSeries(int selectedSeries);
    void setSelectedBook(int selectedBook);
    void refreshData();
    QString getCurrentLibraryName() const;
    void doSearch(const QString &searchTerm);

private:
    Library* defaultLibrary{nullptr};
    Series* currentSeries{nullptr};
    Book* currentBook{nullptr};
    LibraryModel* m_libraryModel{nullptr};
    SeriesModel* m_seriesModel{nullptr};
    BookModel* m_bookModel{nullptr};
    SearchModel* m_searchModel{nullptr};
    int m_currentImageNumber{0};
    int selectedSeriesIdx{-1};
    int selectedLibraryIdx{MasterController::DEFAULT_LIBRARY_ID};
    int selectedBookIdx{-1};
    NetworkInformer* m_networkInformer{nullptr};

};

#endif // MASTERCONTROLLER_H
