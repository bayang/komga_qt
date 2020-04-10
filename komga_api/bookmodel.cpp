#include "bookmodel.h"

BookModel::BookModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}, m_books{}
{
    connect(m_api, &Komga_api::booksDataReady,
            this, &BookModel::apiDataReceived);
}
int BookModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_books.count();
}
QVariant BookModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_books.count())
        return QVariant();

    const Book* book = m_books[index.row()];
    if (role == NameRole)
        return book->name();
    else if (role == IdRole)
        return book->id();
    else if (role == SeriesIdRole)
        return book->seriesId();
    else if (role == NumberRole)
        return book->bookMetadata()->number();
    else if (role == UrlRole)
        return book->url();
    else if (role == SizeBytesRole)
        return book->sizeBytes();
    else if (role == SizeRole)
        return book->size();
    else if (role == MediaStatusRole)
        return book->mediaStatus();
    else if (role == MediaTypeRole)
        return book->mediaType();
    else if (role == PageCountRole)
        return book->pagesCount();
    else if (role == SummaryRole)
        return book->bookMetadata()->summary();
    else if (role == PublisherRole)
        return book->bookMetadata()->publisher();
    else if (role == ReleaseDateRole)
        return book->bookMetadata()->releaseDate();
    else if (role == AuthorsRole)
        return book->bookMetadata()->authors().join(",");
    else if (role == AgeRatingRole)
        return book->bookMetadata()->ageRating();
    return QVariant();
}
QHash<int, QByteArray> BookModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "bookId";
        roles[NameRole] = "bookName";
        roles[SeriesIdRole] = "bookSeriesId";
        roles[NumberRole] = "bookNumber";
        roles[UrlRole] = "bookUrl";
        roles[SizeBytesRole] = "bookSizeBytes";
        roles[SizeRole] = "bookSize";
        roles[MediaStatusRole] = "bookMediaStatus";
        roles[MediaTypeRole] = "bookMediaType";
        roles[PageCountRole] = "bookPageCount";
        roles[SummaryRole] = "bookSummary";
        roles[PublisherRole] = "bookPublisher";
        roles[ReleaseDateRole] = "bookReleaseDate";
        roles[AuthorsRole] = "bookAuthors";
        roles[AgeRatingRole] = "bookAgeRating";
        return roles;
}
void BookModel::loadBooks(int seriesId) {
    m_api->getBooks(seriesId);
}
void BookModel::apiDataReceived(QList<Book*> books) {
    beginResetModel();
    m_books = std::move(books);
    endResetModel();
}
Book* BookModel::get(int index) {
    return m_books.at(index);
}
QByteArray BookModel::getThumbnail(int id) {
    QByteArray a = m_api->getThumbnail(id, Komga_api::ThumbnailType::BookThumbnail);
    return a;
}
