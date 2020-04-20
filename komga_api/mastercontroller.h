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
    Q_PROPERTY( Book* ui_currentBook READ getCurrentBook NOTIFY currentBookChanged )
    Q_PROPERTY( Library* ui_defautLibrary READ getDefaultLibrary WRITE setDefaultLibrary NOTIFY defaultLibraryChanged )
    Q_PROPERTY( Series* ui_currentSeries READ getCurrentSeries NOTIFY currentSeriesChanged )
    Q_PROPERTY( SeriesModel* ui_seriesModel READ getSeriesModel CONSTANT )
    Q_PROPERTY( QSortFilterProxyModel* ui_seriesProxyModel READ getProxyModel CONSTANT )
    Q_PROPERTY( BookModel* ui_bookModel READ getBookModel CONSTANT )
    Q_PROPERTY( LibraryModel* ui_libraryModel READ getLibraryModel CONSTANT )
    Q_PROPERTY( int ui_defaultLibraryId MEMBER DEFAULT_LIBRARY_ID CONSTANT )
    Q_PROPERTY( int ui_currPageNumber READ getCurrentImageNumber WRITE setCurrentImageNumber NOTIFY currentImageNumberChanged )
    Q_PROPERTY( QString ui_currentLibraryName READ getCurrentLibraryName NOTIFY currentLibraryNameChanged )

public:
    explicit MasterController(SeriesModel *seriesModel, BookModel *bookModel, SeriesFilterSortProxyModel *proxyModel, QObject *parent = nullptr);

    static const int DEFAULT_LIBRARY_ID{-100};

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

signals:
    void goSeriesView();
    void goBooksView();
    void goBookDetailView();
    void goBookReadView();
    void currentBookChanged(Book* book);
    void currentLibraryChanged(int id);
    void currentLibraryNameChanged(QString name);
//    void currentSeriesNameChanged(QString name);
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
    QString getCurrentLibraryName() const;
//    QString getCurrentSeriesName() const;

private:
    Library* defaultLibrary{nullptr};
    Series* currentSeries{nullptr};
    Book* currentBook{nullptr};
    LibraryModel* m_libraryModel{nullptr};
    SeriesModel* m_seriesModel{nullptr};
    SeriesFilterSortProxyModel* m_proxyModel{nullptr};
    BookModel* m_bookModel{nullptr};
    int m_currentImageNumber{0};
    int selectedSeriesIdx{0};
    int selectedLibraryIdx{MasterController::DEFAULT_LIBRARY_ID};
    int selectedBookIdx{0};

};

#endif // MASTERCONTROLLER_H
