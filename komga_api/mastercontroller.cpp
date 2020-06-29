#include "mastercontroller.h"

const QString MasterController::SERIES_NEW_NAME{"New series"};
const QString MasterController::SERIES_LATEST_NAME{"Latest series"};
const QString MasterController::SERIES_UPDATED_NAME{"Updated series"};
const QString MasterController::DEFAULT_LIBRARY_NAME{"All libraries"};
const QString MasterController::BOOKS_LATEST_NAME{"Recently added books"};
const QString MasterController::BOOKS_READING_NAME{"Keep reading"};
const QString MasterController::COLLECTIONS_NAME{"Collections"};

MasterController::MasterController(SeriesModel* seriesModel, BookModel* bookModel, CollectionModel* collectionModel, NetworkInformer *informer, QObject *parent) :
    m_seriesModel{seriesModel}, m_bookModel{bookModel}, m_collectionModel{collectionModel}, m_networkInformer{informer}, QObject{parent}
{
    connect(this, &MasterController::loadBooksView, m_bookModel, &BookModel::loadBooks);
    connect(this, &MasterController::loadSeriesView, m_seriesModel, &SeriesModel::loadSeries);
    connect(this, &MasterController::loadCollectionSeriesView, m_seriesModel, &SeriesModel::loadCollectionSeries);
    connect(this, &MasterController::loadCollectionsView, m_collectionModel, &CollectionModel::loadCollections);
}

BookModel *MasterController::getBookModel() const
{
    return m_bookModel;
}

SeriesModel *MasterController::getSeriesModel() const
{
    return m_seriesModel;
}

LibraryModel *MasterController::getLibraryModel() const
{
    return m_libraryModel;
}

void MasterController::nextSeriesPage(int currentLibraryId) {
    if (currentLibraryId == MasterController::DEFAULT_LIBRARY_ID) {
        m_seriesModel->nextSeriesPage(MasterController::DEFAULT_LIBRARY_ID);
    }
    else {
        m_seriesModel->nextSeriesPage(currentLibraryId);
    }
}
void MasterController::nextCollectionsSeriesPage(int currentCollectionId) {
    m_seriesModel->nextCollectionsSeriesPage(currentCollectionId);
}
void MasterController::nextBooksPage(int currentSeriesId) {
    m_bookModel->nextBooksPage(currentSeriesId);
}

void MasterController::nextCollectionsPage()
{
    m_collectionModel->nextCollectionsPage();
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
}

void MasterController::updateprogress(int bookId, int currentPage) {
    getBookModel()->updateProgress(bookId, currentPage);
}

CollectionModel *MasterController::getCollectionModel() const
{
    return m_collectionModel;
}

void MasterController::setCollectionModel(CollectionModel *collectionModel)
{
    m_collectionModel = collectionModel;
}

void MasterController::setSearchModel(SearchModel *searchModel)
{
    m_searchModel = searchModel;
}

void MasterController::setLibraryModel(LibraryModel *libraryModel)
{
    m_libraryModel = libraryModel;
}

void MasterController::setCurrentBookPageReached(int currentImageNumber)
{
    qDebug() << "current image nb changed in controller " << currentImageNumber ;
    getBookModel()->setData(getBookModel()->index(getSelectedBookIdx(), 0), QVariant{currentImageNumber}, BookModel::PageReachedRole);
}

SearchModel *MasterController::getSearchModel() const
{
    return m_searchModel;
}

void MasterController::preloadBookPages(int bookId, int currentPage, int pageCount)
{
    for (int i = 1; i <= 5; i++) {
        if ((currentPage + i < pageCount) && (! getBookModel()->hasImageInCache(bookId, currentPage + i))) {
            getBookModel()->preloadPage(bookId, currentPage + i);
        }
        if ((currentPage - i >= 0) && (! getBookModel()->hasImageInCache(bookId, currentPage - i))) {
            getBookModel()->preloadPage(bookId, currentPage - i);
        }
    }
}

NetworkInformer *MasterController::getNetworkInformer() const
{
    return m_networkInformer;
}

void MasterController::doSearch(const QString &searchTerm) {
    m_searchModel->doSearch(searchTerm);
}

void MasterController::resetSearch() {
    getSearchModel()->resetModel();
}
