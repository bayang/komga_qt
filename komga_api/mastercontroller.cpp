#include "mastercontroller.h"

MasterController::MasterController(SeriesModel* seriesModel, BookModel* bookModel, SeriesFilterSortProxyModel *proxyModel, QObject *parent) :
    m_seriesModel{seriesModel}, m_bookModel{bookModel}, m_proxyModel{proxyModel}, QObject{parent}, defaultLibrary{new Library()}
{
    defaultLibrary->setId(MasterController::DEFAULT_LIBRARY_ID);
    defaultLibrary->setName("All libraries");
    connect(this, &MasterController::currentSeriesChanged, m_bookModel, &BookModel::loadBooks);
}
void MasterController::setSelectedLibrary(int selectedLibrary) {
    qDebug() << "selected library in mastercontroller : " << selectedLibrary;
    if (selectedLibrary == MasterController::DEFAULT_LIBRARY_ID) {
        setCurrentLibrary(getDefaultLibrary());
    }
    else {
        setCurrentLibrary(getLibraryModel()->get(selectedLibrary));
    }
}
void MasterController::setSelectedSeries(int selectedSeries) {
    qDebug() << "selected series in mastercontroller : " << selectedSeries;
    if (selectedSeries >= 0) {
        QModelIndex proxIdx = m_proxyModel->index(selectedSeries, 0);
        QModelIndex srcIdx = m_proxyModel->mapToSource(proxIdx);
        qDebug() << "proxIdx : " << proxIdx.row() << " srcIdx " << srcIdx.row();
        setCurrentSeries(m_seriesModel->get(srcIdx.row()));
    }
}
void MasterController::setSelectedBook(int selectedBook) {
    qDebug() << "selected book in mastercontroller : " << selectedBook;
    if (selectedBook >= 0 && selectedBook < getBookModel()->rowCount(QModelIndex())) {
        setCurrentBook(getBookModel()->get(selectedBook));
    }
}

SeriesFilterSortProxyModel *MasterController::getProxyModel() const
{
    return m_proxyModel;
}

void MasterController::setProxyModel(SeriesFilterSortProxyModel *proxyModel)
{
    m_proxyModel = proxyModel;
}

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

Series *MasterController::getCurrentSeries() const
{
    return currentSeries;
}

void MasterController::setCurrentSeries(Series *value)
{
    qDebug() << "setCurrentSeries " << value->name();
    if (value && value != currentSeries) {
        currentSeries = value;
        emit currentSeriesChanged(value);
    }
}

Library *MasterController::getCurrentLibrary() const
{
    return currentLibrary;
}

void MasterController::setCurrentLibrary(Library *value)
{
    qDebug() << "setCurrentLibrary " << value->name();
    if (value != currentLibrary) {
        currentLibrary = value;
        m_proxyModel->setLibraryId(currentLibrary->id());
        emit currentLibraryChanged(value);
    }
}

Book *MasterController::getCurrentBook() const
{
    return currentBook;
}

void MasterController::setCurrentBook(Book *value)
{
    if (value != currentBook) {
        currentBook = value;
        setCurrentImageNumber(0);
        emit currentBookChanged(value);
    }
}

void MasterController::nextSeriesPage() {
    m_seriesModel->nextSeriesPage(getCurrentLibrary());
}
void MasterController::nextBooksPage() {
    m_bookModel->nextBooksPage(getCurrentSeries());
}
void MasterController::refreshData() {
    m_libraryModel->fetchData();
    m_seriesModel->loadSeries(getDefaultLibrary());
}

int MasterController::getCurrentImageNumber() const
{
    return m_currentImageNumber;
}

void MasterController::setCurrentImageNumber(int currentImageNumber)
{
    if (currentImageNumber != m_currentImageNumber) {
        if (currentImageNumber >= 0 && currentImageNumber < getCurrentBook()->pagesCount()) {
            qDebug() << "current image nb changed in controller " << currentImageNumber ;
            m_currentImageNumber = currentImageNumber;
            emit currentImageNumberChanged(currentImageNumber);
        }
    }
}
