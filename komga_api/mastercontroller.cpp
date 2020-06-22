#include "mastercontroller.h"

const QString MasterController::SERIES_NEW_NAME{"New series"};
const QString MasterController::SERIES_LATEST_NAME{"Latest series"};
const QString MasterController::SERIES_UPDATED_NAME{"Updated series"};
const QString MasterController::BOOKS_CURRENTLY_READING_NAME{"Continue Reading"};


MasterController::MasterController(SeriesModel* seriesModel, BookModel* bookModel, NetworkInformer *informer, QObject *parent) :
    m_seriesModel{seriesModel}, m_bookModel{bookModel}, m_networkInformer{informer}, QObject{parent},
    defaultLibrary{new Library(this)}, currentSeries{new Series(this)}, currentBook{new Book(this)}
{
    defaultLibrary->setId(MasterController::DEFAULT_LIBRARY_ID);
    defaultLibrary->setName("All libraries");
//    connect(this, &MasterController::currentSeriesChanged, m_bookModel, &BookModel::loadBooks);
    connect(this, &MasterController::goBooksView, m_bookModel, &BookModel::loadBooks);
//    connect(this, &MasterController::currentLibraryChanged, m_seriesModel, &SeriesModel::loadSeries);
    connect(this, &MasterController::goSeriesView, m_seriesModel, &SeriesModel::loadSeries);
}
//void MasterController::setSelectedLibrary(int selectedLibrary) {
//    qDebug() << "selected library in mastercontroller : " << selectedLibrary;
//    setSelectedLibraryIdx(selectedLibrary);
//}
//void MasterController::setSelectedSeries(int selectedSeries) {
//    qDebug() << "selected series in mastercontroller : " << selectedSeries;
//    if (selectedSeries >= 0) {
//        setSelectedSeriesIdx(selectedSeries);
//    }
//}
//void MasterController::setSelectedBook(int selectedBook) {
//    qDebug() << "selected book in mastercontroller : " << selectedBook;
//    if (selectedBook >= 0 && selectedBook < getBookModel()->rowCount(QModelIndex())) {
//        setSelectedBookIdx(selectedBook);
//    }
//}

BookModel *MasterController::getBookModel() const
{
    return m_bookModel;
}

void MasterController::setBookModel(BookModel *bookModel)
{
    m_bookModel = bookModel;
}

SeriesModel *MasterController::getSeriesModel() const
{
    return m_seriesModel;
}

void MasterController::setSeriesModel(SeriesModel *seriesModel)
{
    m_seriesModel = seriesModel;
}

LibraryModel *MasterController::getLibraryModel() const
{
    return m_libraryModel;
}

void MasterController::setLibraryModel(LibraryModel *libraryModel)
{
    m_libraryModel = libraryModel;
}

Library *MasterController::getDefaultLibrary() const
{
    return defaultLibrary;
}

void MasterController::setDefaultLibrary(Library *value)
{
    qDebug() << "setDefaultLibrary " << value->name();
    if (value != defaultLibrary) {
        defaultLibrary = value;
        emit defaultLibraryChanged();
    }
}

//Series *MasterController::getCurrentSeries() const
//{
//    return currentSeries;
//}

//Book *MasterController::getCurrentBook() const
//{
//    return currentBook;
//}

void MasterController::nextSeriesPage(int currentLibraryId) {
    if (currentLibraryId == MasterController::DEFAULT_LIBRARY_ID) {
        m_seriesModel->nextSeriesPage(MasterController::DEFAULT_LIBRARY_ID);
    }
    else {
        m_seriesModel->nextSeriesPage(currentLibraryId);
    }
}
void MasterController::nextBooksPage(int currentSeriesId) {
    m_bookModel->nextBooksPage(currentSeriesId);
}
void MasterController::refreshData() {
    m_libraryModel->fetchData();
    m_seriesModel->loadSeries(MasterController::DEFAULT_LIBRARY_ID);
}

int MasterController::getSelectedBookIdx() const
{
    return selectedBookIdx;
}

void MasterController::setSelectedBookIdx(int value)
{
    selectedBookIdx = value;
//    qDebug() << "setSelectedBook " << value;
//    if (value < 0) {
//        selectedBookIdx = value;
//        return;
//    }
//    if (value != selectedBookIdx) {
//        selectedBookIdx = value;
//        currentBook->setId(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::IdRole).toInt());
//        currentBook->setUrl(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::UrlRole).toString());
//        currentBook->setName(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::NameRole).toString());
//        currentBook->setSize(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::SizeRole).toString());
//        currentBook->setNumber(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::NumberRole).toInt());
//        currentBook->setPagesCount(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::PageCountRole).toInt());
//        currentBook->setMediaType(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::MediaTypeFullRole).toString());
//        currentBook->setMediaStatus(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::MediaStatusRole).toString());
//        currentBook->bookMetadata()->setTitle(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::TitleRole).toString());
//        currentBook->bookMetadata()->setSummary(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::SummaryRole).toString());
//        currentBook->bookMetadata()->setPublisher(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::PublisherRole).toString());
//        currentBook->bookMetadata()->setReleaseDate(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::ReleaseDateRole).toString());
//        QVariant qv = getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::AuthorsRole);
//        QSequentialIterable iterable = qv.value<QSequentialIterable>();
//        QList<Author*> as{};
//        currentBook->bookMetadata()->authors().clear();
//        for (const QVariant &v : iterable) {
//            Author* a = v.value<Author*>();
//            Author* copy = new Author(currentBook->bookMetadata());
//            copy->setName(a->name());
//            copy->setRole(a->role());
//            as.append(std::move(copy));
//        }
//        currentBook->bookMetadata()->setAuthors(as);
//        currentBook->bookMetadata()->setAgeRating(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::AgeRatingRole).toString());
//        currentBook->setCompleted(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::CompletedRole).toBool());
//        currentBook->setPageReached(getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::PageReachedRole).toInt());
//        emit currentBookChanged(getCurrentBook());
//    }
}

//int MasterController::getSelectedLibraryIdx() const
//{
//    return selectedLibraryIdx;
//}

//void MasterController::setSelectedLibraryIdx(int value)
//{
//    qDebug() << "setCurrentLibraryIdx " << value;
//    if (value != selectedLibraryIdx) {
//        selectedLibraryIdx = value;
//        setSelectedSeriesIdx(-1);
//        setSelectedBookIdx(-1);
//        if (value == MasterController::DEFAULT_LIBRARY_ID) {
//            emit currentLibraryChanged(MasterController::DEFAULT_LIBRARY_ID);
//            emit currentLibraryNameChanged(getDefaultLibrary()->name());
//        }
//        else if (value == MasterController::SERIES_NEW_ID) {
//            emit currentLibraryChanged(MasterController::SERIES_NEW_ID);
//            emit currentLibraryNameChanged(MasterController::SERIES_NEW_NAME);
//        }
//        else if (value == MasterController::SERIES_LATEST_ID) {
//            emit currentLibraryChanged(MasterController::SERIES_LATEST_ID);
//            emit currentLibraryNameChanged(MasterController::SERIES_LATEST_NAME);
//        }
//        else if (value == MasterController::SERIES_UPDATED_ID) {
//            emit currentLibraryChanged(MasterController::SERIES_UPDATED_ID);
//            emit currentLibraryNameChanged(MasterController::SERIES_UPDATED_NAME);
//        }
//        else {
//            emit currentLibraryChanged(getLibraryModel()->data(getLibraryModel()->index(value, 0), LibraryModel::LibraryRoles::IdRole).toInt());
//            emit currentLibraryNameChanged(getLibraryModel()->data(getLibraryModel()->index(value, 0), LibraryModel::LibraryRoles::NameRole).toString());
//        }
//    }
//}

//int MasterController::getSelectedSeriesIdx() const
//{
//    return selectedSeriesIdx;
//}

//void MasterController::setSelectedSeriesIdx(int value)
//{
//    qDebug() << "setCurrentSeries " << value;
//    if (value < 0) {
//        selectedSeriesIdx = value;
//        return;
//    }
//    if (value != selectedSeriesIdx) {
//        selectedSeriesIdx = value;
//        setSelectedBookIdx(-1);
//        currentSeries->setId(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::IdRole).toInt());
//        QString qs = getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::NameRole).toString();
//        currentSeries->setName(qs);
//        currentSeries->setMetadataStatus(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::MetadataStatusRole).toString());
//        currentSeries->setBooksCount(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::BookCountRole).toInt());
//        currentSeries->setBooksReadCount(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::BookReadCountRole).toInt());
//        currentSeries->setBooksUnreadCount(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::BookUnreadCountRole).toInt());
//        currentSeries->setBooksInProgressCount(getSeriesModel()->data(getSeriesModel()->index(getSelectedSeriesIdx(), 0), SeriesModel::SeriesRoles::BookInProgressCountRole).toInt());
//        emit currentSeriesChanged(getCurrentSeries());
//    }
//}

void MasterController::setCurrentBookPageReached(int currentImageNumber)
{
    qDebug() << "current image nb changed in controller " << currentImageNumber ;
//    getCurrentBook()->setPageReached(currentImageNumber);
    getBookModel()->setData(getBookModel()->index(getSelectedBookIdx(), 0), QVariant{currentImageNumber}, BookModel::PageReachedRole);
//    if (currentImageNumber < 0) {
//        emit firstBookPageReached();
//        return;
//    }
//    else if (currentImageNumber >= getCurrentBook()->pagesCount()) {
//        emit lastBookPageReached();
//        return;
//    }
//    else {
//    }
//    if (currentImageNumber != getCurrentBook()->pageReached()) {
//    }
}
//QString MasterController::getCurrentLibraryName() const {
//    if (getSelectedLibraryIdx() == MasterController::DEFAULT_LIBRARY_ID) {
//        return getDefaultLibrary()->name();
//    }
//    else if (getSelectedLibraryIdx() == MasterController::SERIES_NEW_ID) {
//        return MasterController::SERIES_NEW_NAME;
//    }
//    else if (getSelectedLibraryIdx() == MasterController::SERIES_LATEST_ID) {
//        return MasterController::SERIES_LATEST_NAME;
//    }
//    else if (getSelectedLibraryIdx() == MasterController::SERIES_UPDATED_ID) {
//        return MasterController::SERIES_UPDATED_NAME;
//    }
//    return getLibraryModel()->data(getLibraryModel()->index(getSelectedLibraryIdx(), 0), LibraryModel::LibraryRoles::NameRole).toString();
//}

SearchModel *MasterController::getSearchModel() const
{
    return m_searchModel;
}

void MasterController::setSearchModel(SearchModel *searchModel)
{
    m_searchModel = searchModel;
}

void MasterController::preloadBookPages(int bookId, int currentPage)
{
    int currentBookPageTotal = getBookModel()->data(getBookModel()->index(getSelectedBookIdx(), 0), BookModel::BooksRoles::PageCountRole).toInt();
    for (int i = 1; i <= 5; i++) {
        if ((currentPage + i < currentBookPageTotal) && (! getBookModel()->hasImageInCache(bookId, currentPage + i))) {
            getBookModel()->preloadPage(bookId, currentPage + i);
        }
        if ((currentPage - i >= 0) && (! getBookModel()->hasImageInCache(bookId, currentPage - i))) {
            getBookModel()->preloadPage(bookId, currentPage - i);
        }
    }
}

QString MasterController::getDefaultLibraryName()
{
    return getDefaultLibrary()->name();
}

NetworkInformer *MasterController::getNetworkInformer() const
{
    return m_networkInformer;
}

void MasterController::setNetworkInformer(NetworkInformer *networkInformer)
{
    m_networkInformer = networkInformer;
}
void MasterController::doSearch(const QString &searchTerm) {
    m_searchModel->doSearch(searchTerm);
}

void MasterController::setSearchResult(int index)
{
    SearchResult* sr = getSearchModel()->at(index);
    if (sr->resultType() == SearchResult::ResultType::BookType) {
//        currentBook->setId(sr->book()->id());
//        currentBook->setUrl(sr->book()->url());
//        currentBook->setName(sr->book()->name());
//        currentBook->setSize(sr->book()->size());
//        currentBook->setNumber(sr->book()->number());
//        currentBook->setPagesCount(sr->book()->pagesCount());
//        currentBook->setMediaType(sr->book()->mediaType());
//        currentBook->setMediaStatus(sr->book()->mediaStatus());
//        currentBook->bookMetadata()->setTitle(sr->book()->bookMetadata()->title());
//        currentBook->bookMetadata()->setSummary(sr->book()->bookMetadata()->summary());
//        currentBook->bookMetadata()->setPublisher(sr->book()->bookMetadata()->publisher());
//        currentBook->bookMetadata()->setReleaseDate(sr->book()->bookMetadata()->releaseDate());
//        currentBook->bookMetadata()->setAuthors(sr->book()->bookMetadata()->authors());
//        currentBook->bookMetadata()->setAgeRating(sr->book()->bookMetadata()->ageRating());
//        currentBook->setCompleted(sr->book()->completed());
//        currentBook->setPageReached(sr->book()->pageReached());
//        emit currentBookChanged(getCurrentBook());
        goBookDetailView(sr->book()->id());
    }
    else {
//        selectedSeriesIdx = -1;
//        setSelectedBookIdx(-1);
//        currentSeries->setId(sr->series()->id());
//        QString qs = sr->series()->name();
//        currentSeries->setName(qs);
//        currentSeries->setMetadataStatus(sr->series()->metadataStatus());
//        currentSeries->setBooksCount(sr->series()->booksCount());
//        currentSeries->setBooksReadCount(sr->series()->booksReadCount());
//        currentSeries->setBooksUnreadCount(sr->series()->booksUnreadCount());
//        currentSeries->setBooksInProgressCount(sr->series()->booksInProgressCount());
//        emit currentSeriesChanged(getCurrentSeries());

        goBooksView(sr->series()->id());
    }
    getSearchModel()->resetModel();
}
