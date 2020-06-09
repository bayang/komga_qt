#include "bookmodel.h"
#include <QJsonArray>

BookModel::BookModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}, m_books{}
{
    connect(m_api, &Komga_api::booksDataReady,
            this, &BookModel::apiDataReceived);
    connect(m_api, &Komga_api::preloadImageDataReady,
            this, &BookModel::preloadImageDataReceived);
}
int BookModel::rowCount(const QModelIndex &parent) const {
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid()) {
        return 0;
    }
    return m_books.count();
}
QVariant BookModel::data(const QModelIndex &index, int role) const {
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));
    if (! index.isValid()) {
        qDebug() << "invalid indx " << index.row();
        return QVariant();
    }
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
        return book->mediaTypeShort();
    else if (role == MediaTypeFullRole)
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
    else if (role == TitleRole)
        return book->bookMetadata()->title();
    else if (role == PageReachedRole)
        return book->pageReached();
    else if (role == CompletedRole)
        return book->completed();
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
        roles[TitleRole] = "bookTitle";
        roles[MediaTypeFullRole] = "bookMediaTypeFull";
        roles[PageReachedRole] = "bookPageReached";
        roles[CompletedRole] = "bookCompleted";
        return roles;
}
void BookModel::loadBooks(Series* series) {
    m_api->getBooks(series->id());
    resetBooks();
}
Book* BookModel::parseBook(const QJsonValue &value) {
    Book* b = new Book(this);
    QJsonObject jsob = value.toObject();
    b->setId(jsob["id"].toInt());
    b->setSeriesId(jsob["seriesId"].toInt());
    b->setName(jsob["name"].toString());
    b->setUrl(jsob["url"].toString());
    b->setSizeBytes(jsob["sizeBytes"].toInt());
    b->setSize(jsob["size"].toString());
    QJsonObject media = jsob["media"].toObject();
    b->setMediaStatus(media["status"].toString());
    b->setPagesCount(media["pagesCount"].toInt());
    b->setMediaType(media["mediaType"].toString());
    BookMetadata* meta = new BookMetadata();
    QJsonObject metadata = jsob["metadata"].toObject();
    meta->setTitle(metadata["title"].toString());
    meta->setSummary(metadata["summary"].toString());
    meta->setNumber(metadata["number"].toString());
    meta->setNumberSort(metadata["numberSort"].toInt());
    meta->setPublisher(metadata["publisher"].toString());
    meta->setAgeRating(metadata["ageRating"].toString());
    meta->setReleaseDate(metadata["releaseDate"].toString());
    QJsonArray authors = metadata["authors"].toArray();
    QList<QString> aut{""};
    foreach (const QJsonValue &value, authors) {
        aut.append(value.toString());
    }
    meta->setAuthors(aut);
    if (jsob.contains("readProgress")) {
        QJsonObject progress = jsob["readProgress"].toObject();
        if (progress.contains("page")) {
            b->setPageReached(progress["page"].toInt());
        }
        if (progress.contains("completed")) {
            b->setCompleted(progress["completed"].toBool());
        }
    }
    b->setBookMetadata(meta);
    return b;
}
void BookModel::apiDataReceived(QJsonObject books) {
    int pageNum = books["number"].toInt();
    int totPages = books["totalPages"].toInt();
    int nbElems = books["numberOfElements"].toInt();
    qDebug() << "page : " << pageNum;
    qDebug() << "page number : " << totPages;
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_books.size(), m_books.size() + nbElems - 1);
            QJsonArray content = books["content"].toArray();
            foreach (const QJsonValue &value, content) {
                m_books.append(std::move(parseBook(value)));
            }
            emit endInsertRows();
        }
        else {
            QList<Book*> booksList{};
            QJsonArray content = books["content"].toArray();
            foreach (const QJsonValue &value, content) {
                booksList.append(std::move(parseBook(value)));
            }
            emit layoutAboutToBeChanged();
            m_books = booksList;
            changePersistentIndex(index(0), QModelIndex());
            emit layoutChanged();
        }
        m_currentPageNumber = pageNum;
        m_totalPageNumber = totPages;
    }
}
QByteArray BookModel::getThumbnail(int id) {
    QByteArray a = m_api->getThumbnail(id, Komga_api::ThumbnailType::BookThumbnail);
    return a;
}
QByteArray BookModel::getPage(int id, int pageNum) {
    QByteArray a = m_api->getPage(id, pageNum);
    return a;
}
void BookModel::nextBooksPage(Series *series) {
    qDebug() << "curr p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getBooks(series->id(), m_currentPageNumber + 1);
    }
}
void BookModel::resetBooks() {
    qDebug() << "reset books";
    emit beginRemoveRows(QModelIndex(), 0, m_books.size() - 1);
    qDeleteAll(m_books);
    m_books.clear();
    emit endRemoveRows();
}
void BookModel::preloadPage(int id, int pageNum) {
    m_api->getPageAsync(id, pageNum);
}
void BookModel::preloadImageDataReceived(QPair<QString, QByteArray> res) {
    if (! res.second.isNull() && ! res.second.isEmpty()) {
        m_picturesCache.insert(res.first, new QByteArray(res.second));
    }
}

void BookModel::updateProgress(int bookId, int page, bool completed)
{
    m_api->updateProgress(bookId, page, completed);
}
QByteArray* BookModel::getImageFromCache(const QString &key) {
    return m_picturesCache[key];
}
