#include "bookmodel.h"
#include <QJsonArray>

BookModel::BookModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}, m_books{}
{
    connect(m_api, &Komga_api::booksDataReady,
            this, &BookModel::apiDataReceived);
    connect(m_api, &Komga_api::preloadImageDataReady,
            this, &BookModel::preloadImageDataReceived);
    connect(m_api, &Komga_api::nextBookReady,
            this, &BookModel::nextBookReceived);
    connect(m_api, &Komga_api::previousBookReady,
            this, &BookModel::previousBookReceived);
}
int BookModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_books.count();
}
QVariant BookModel::data(const QModelIndex &index, int role) const {
    if (! index.isValid()) {
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
    else if (role == ReleaseDateRole)
        return book->bookMetadata()->releaseDate();
    else if (role == AuthorsRole)
        return QVariant::fromValue(book->bookMetadata()->authors());
    else if (role == TitleRole)
        return book->bookMetadata()->title();
    else if (role == PageReachedRole)
        return book->pageReached();
    else if (role == CompletedRole)
        return book->completed();
    else if (role == WritersRole)
        return book->bookMetadata()->writersAsString();
    else if (role == PencillersRole)
        return book->bookMetadata()->pencillersAsString();
    else if (role == ColoristsRole)
        return book->bookMetadata()->coloristsAsString();
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
        roles[ReleaseDateRole] = "bookReleaseDate";
        roles[AuthorsRole] = "bookAuthors";
        roles[TitleRole] = "bookTitle";
        roles[MediaTypeFullRole] = "bookMediaTypeFull";
        roles[PageReachedRole] = "bookPageReached";
        roles[CompletedRole] = "bookCompleted";
        roles[WritersRole] = "bookWriters";
        roles[PencillersRole] = "bookPencillers";
        roles[ColoristsRole] = "bookColorists";
        return roles;
}
void BookModel::loadBooks(QString seriesId) {
    m_api->getBooks(seriesId);
    resetBooks();
}
void BookModel::loadReadListBooks(QString readListId) {
    m_api->getReadListBooks(readListId);
    resetBooks();
}
Book* BookModel::parseBook(const QJsonValue &value, QObject* parent) {
    return parseBook(value.toObject(), parent);
}
Book* BookModel::parseBook(const QJsonObject &object, QObject* parent) {
    Book* b = new Book(parent);
    if (object.empty()) {
        b->setId("-1");
        return b;
    }
//    QJsonObject jsob = value.toObject();
    b->setId(object["id"].toString());
    b->setSeriesId(object["seriesId"].toString());
    b->setName(object["name"].toString());
    b->setUrl(object["url"].toString());
    b->setSizeBytes(object["sizeBytes"].toInt());
    b->setSize(object["size"].toString());
    QJsonObject media = object["media"].toObject();
    b->setMediaStatus(media["status"].toString());
    b->setPagesCount(media["pagesCount"].toInt());
    b->setMediaType(media["mediaType"].toString());
    BookMetadata* meta = new BookMetadata(b);
    QJsonObject metadata = object["metadata"].toObject();
    meta->setTitle(metadata["title"].toString());
    meta->setSummary(metadata["summary"].toString());
    meta->setNumber(metadata["number"].toString());
    meta->setNumberSort(metadata["numberSort"].toInt());
    meta->setReleaseDate(metadata["releaseDate"].toString());
    QJsonArray authors = metadata["authors"].toArray();
    QList<Author*> aut{};
    foreach (const QJsonValue &value, authors) {
        QJsonObject ob = value.toObject();
        Author* au = new Author(meta);
        au->setName(ob["name"].toString());
        au->setRole(ob["role"].toString());
        aut.append(std::move(au));
    }
    meta->setAuthors(aut);
    if (object.contains("readProgress")) {
        QJsonObject progress = object["readProgress"].toObject();
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

bool BookModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (! index.isValid()) {
        return false;
    }
    Book* b = m_books.at(index.row());
    if (role == PageReachedRole) {
        b->setPageReached(value.toInt());
        if (b->pageReached() + 1 == b->pagesCount()) {
            b->setCompleted(true);
        }
    }
    else if (role == CompletedRole) {
        b->setCompleted(value.toBool());
    }
    emit dataChanged(index, index);
    return true;
}

void BookModel::previousBook(QString bookId)
{
    m_api->previousBook(bookId);
}

void BookModel::nextBook(QString bookId)
{
    m_api->nextBook(bookId);
}
void BookModel::apiDataReceived(QJsonObject books) {
    int pageNum = books["number"].toInt();
    int totPages = books["totalPages"].toInt();
    int nbElems = books["numberOfElements"].toInt();
    if (nbElems > 0) {
        if (pageNum > 0) {
            emit beginInsertRows(QModelIndex(), m_books.size(), m_books.size() + nbElems - 1);
            QJsonArray content = books["content"].toArray();
            foreach (const QJsonValue &value, content) {
                m_books.append(std::move(parseBook(value, this)));
            }
            emit endInsertRows();
        }
        else {
            QList<Book*> booksList{};
            QJsonArray content = books["content"].toArray();
            foreach (const QJsonValue &value, content) {
                booksList.append(std::move(parseBook(value, this)));
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
QByteArray BookModel::getPage(QString id, int pageNum) {
    QByteArray a = m_api->getPage(id, pageNum);
    return a;
}
void BookModel::nextBooksPage(QString seriesId) {
    qDebug() << "curr p :" << m_currentPageNumber << " total p : " << m_totalPageNumber;
    if (m_currentPageNumber + 1 < m_totalPageNumber) {
        m_api->getBooks(seriesId, m_currentPageNumber + 1);
    }
}
void BookModel::resetBooks() {
    emit beginRemoveRows(QModelIndex(), 0, m_books.size() - 1);
    qDeleteAll(m_books);
    m_books.clear();
    emit endRemoveRows();
}
void BookModel::preloadPage(QString id, int pageNum) {
    m_api->getPageAsync(id, pageNum);
}
void BookModel::preloadImageDataReceived(QPair<QString, QByteArray> res) {
    if (! res.second.isNull() && ! res.second.isEmpty()) {
        m_picturesCache.insert(res.first, new QByteArray(res.second));
    }
}

void BookModel::updateProgress(QString bookId, int page, bool completed)
{
    m_api->updateProgress(bookId, page, completed);
}

void BookModel::nextBookReceived(QJsonObject book)
{
    emit nextBookReady(std::move(parseBook(book, this)));
}

void BookModel::previousBookReceived(QJsonObject book)
{
    emit previousBookReady(std::move(parseBook(book, this)));
}
QByteArray* BookModel::getImageFromCache(const QString &key) {
    return m_picturesCache[key];
}

bool BookModel::hasImageInCache(QString bookId, int currentPage)
{
    return m_picturesCache.contains(bookId + "/"+QString::number(currentPage));
}
