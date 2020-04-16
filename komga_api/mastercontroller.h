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

class KOMGA_API_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( Book* ui_currentBook READ getCurrentBook WRITE setCurrentBook NOTIFY currentBookChanged )
    Q_PROPERTY( Library* ui_currentLibrary READ getCurrentLibrary WRITE setCurrentLibrary NOTIFY currentLibraryChanged )
    Q_PROPERTY( Library* ui_defautLibrary READ getDefaultLibrary WRITE setDefaultLibrary NOTIFY defaultLibraryChanged )
    Q_PROPERTY( Series* ui_currentSeries READ getCurrentSeries WRITE setCurrentSeries NOTIFY currentSeriesChanged )
    Q_PROPERTY( SeriesModel* ui_baseSeriesModel READ getSeriesModel CONSTANT )
    Q_PROPERTY( QSortFilterProxyModel* ui_seriesModel READ getProxyModel CONSTANT )
    Q_PROPERTY( BookModel* ui_bookModel READ getBookModel CONSTANT )
    Q_PROPERTY( LibraryModel* ui_libraryModel READ getLibraryModel CONSTANT )
    Q_PROPERTY( int ui_defaultLibraryId MEMBER DEFAULT_LIBRARY_ID CONSTANT )
    Q_PROPERTY( int ui_currPageNumber READ getCurrentImageNumber WRITE setCurrentImageNumber NOTIFY currentImageNumberChanged )


public:
    explicit MasterController(SeriesModel *seriesModel, BookModel *bookModel, SeriesFilterSortProxyModel *proxyModel, QObject *parent = nullptr);

    static const int DEFAULT_LIBRARY_ID{-100};

    Book *getCurrentBook() const;
    void setCurrentBook(Book *value);

    Library *getCurrentLibrary() const;
    void setCurrentLibrary(Library *value);

    Series *getCurrentSeries() const;
    void setCurrentSeries(Series *value);

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

signals:
    void goSeriesView();
    void goBooksView();
    void goBookDetailView();
    void goBookReadView();
    void currentBookChanged(Book* book);
    void currentLibraryChanged(Library* library);
    void defaultLibraryChanged();
    void currentSeriesChanged(Series *series);
    void currentImageNumberChanged(int newValue);

public slots:
    void nextSeriesPage();
    void nextBooksPage();
    void setSelectedLibrary(int selectedLibrary);
    void setSelectedSeries(int selectedSeries);
    void setSelectedBook(int selectedBook);
    void refreshData();

private:
    Book* currentBook{nullptr};
    Library* currentLibrary{nullptr};
    Series* currentSeries{nullptr};
    Library* defaultLibrary{nullptr};
    LibraryModel* m_libraryModel{nullptr};
    SeriesModel* m_seriesModel{nullptr};
    SeriesFilterSortProxyModel* m_proxyModel{nullptr};
    BookModel* m_bookModel{nullptr};
    int m_currentImageNumber{0};
    int
};

#endif // MASTERCONTROLLER_H
