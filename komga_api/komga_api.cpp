#include "komga_api.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QVariant>
#include <QEventLoop>
#include <QSettings>
#include <QNetworkConfigurationManager>
#include "mastercontroller.h"
#include <QSignalMapper>

const QString Komga_api::URL_LIBRARIES{"/libraries"};
const QString Komga_api::URL_SERIES{"/series"};
const QString Komga_api::URL_LATEST{"/latest"};
const QString Komga_api::URL_ONDECK{"/ondeck"};
const QString Komga_api::URL_SERIES_NEW{"/new"};
const QString Komga_api::URL_SERIES_UPDATED{"/updated"};
const QString Komga_api::URL_BOOKS{"/books"};
const QString Komga_api::URL_THUMBNAILS{"/thumbnail"};
const QString Komga_api::URL_PAGE{"/pages"};
const QString Komga_api::URL_PROGRESS{"read-progress"};
const QString Komga_api::URL_COLLECTIONS{"/collections"};
const QString Komga_api::URL_NEXT{"/next"};
const QString Komga_api::URL_PREVIOUS{"/previous"};
const QString Komga_api::SETTINGS_SECTION_SERVER{"server"};
const QString Komga_api::SETTINGS_KEY_SERVER_URL{"serverAdress"};
const QString Komga_api::SETTINGS_KEY_SERVER_USER{"serverUsername"};
const QString Komga_api::SETTINGS_KEY_SERVER_PASSWORD{"serverPassword"};

Komga_api::Komga_api(QObject *parent):
    QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    QNetworkConfigurationManager confManager;
    manager->setConfiguration(confManager.defaultConfiguration());
    m_mapper = new QSignalMapper(this);
    m_searchMapper = new QSignalMapper(this);
    thumbnailsManager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Komga_api::apiReplyFinished);
    connect(manager, &QNetworkAccessManager::authenticationRequired,
            this, &Komga_api::authenticate);
    connect(manager, &QNetworkAccessManager::sslErrors,
            this, &Komga_api::onSslErrors);
    connect(thumbnailsManager, &QNetworkAccessManager::authenticationRequired, [=](QNetworkReply *reply, QAuthenticator *authenticator){
        Q_UNUSED(reply);
        qDebug() << "[net] authentication tm";
        QSettings settings;
        settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
        QString user = settings.value(Komga_api::SETTINGS_KEY_SERVER_USER).toString();
        QString pw = settings.value(Komga_api::SETTINGS_KEY_SERVER_PASSWORD).toString();
        settings.endGroup();
        authenticator->setUser(user);
        authenticator->setPassword(pw);
    });
    connect(m_mapper, QOverload<const QString &>::of(&QSignalMapper::mapped), this,
        &Komga_api::preloadImageReady);
    connect(m_searchMapper, QOverload<const QString &>::of(&QSignalMapper::mapped), this,
        &Komga_api::searchDataReceived);
    connect(manager, &QNetworkAccessManager::networkAccessibleChanged, [this](QNetworkAccessManager::NetworkAccessibility accessible){
        qDebug() << "[net] network available " << accessible;
        if (accessible == QNetworkAccessManager::NetworkAccessibility::NotAccessible) {
            emit netWorkAccessibleChanged(false);
        }
        else {
            emit netWorkAccessibleChanged(true);
        }
    });

}

void Komga_api::searchDataReceived(const QString &id) {
    QNetworkReply *reply = m_replies.take(id);
    if (reply->error() == QNetworkReply::NoError) {
        QPair<QString, QJsonDocument> res;
        res.first = id;
        QByteArray response(reply->readAll());
        res.second = QJsonDocument::fromJson(response);
        if (id.contains(URL_SERIES)) {
            emit searchSeriesDataReady(res);
        }
        else if (id.contains(URL_BOOKS)) {
            emit searchBookDataReady(res);
        }
        else if (id.contains(URL_COLLECTIONS)) {
            emit searchCollectionsDataReady(res);
        }
    }
    reply->deleteLater();
}

void Komga_api::preloadImageReady(const QString &id) {
    QNetworkReply *reply = m_replies.take(id);
    if (reply && reply->error() == QNetworkReply::NoError) {
        QPair<QString, QByteArray> res;
        res.first = id;
        res.second = reply->readAll();
        emit preloadImageDataReady(res);
    }
    reply->deleteLater();
}
void Komga_api::getLibraries() {
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Libraries));
    QUrl url;
    url.setUrl(getServerUrl() + URL_LIBRARIES);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getCollections(int page) {
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Collections));
    QUrl url;
    url.setUrl(getServerUrl() + URL_COLLECTIONS);
    r.setUrl(url);
    if (page != 0) {
        QUrlQuery query;
        query.addQueryItem("page", QString::number(page));
        url.setQuery(query);
    }
    qDebug() << "api load collections " << url;
    manager->get(r);
}

void Komga_api::previousBook(QString bookId)
{
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::PreviousBook));
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + bookId + URL_PREVIOUS);
    r.setUrl(url);
    qDebug() << "api previous book " << url << " " << bookId;
    manager->get(r);
}

void Komga_api::nextBook(QString bookId)
{
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::NextBook));
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + bookId + URL_NEXT);
    r.setUrl(url);
    qDebug() << "api next book " << url << " " << bookId;
    manager->get(r);
}

void Komga_api::getSeries(QString libraryId, int page) {
    qDebug() << "fetching series for library " << libraryId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesReason));
    QUrl url;
    if (libraryId == MasterController::SERIES_NEW_ID) {
        url.setUrl(getServerUrl() + URL_SERIES + URL_SERIES_NEW);
    }
    else if (libraryId == MasterController::SERIES_LATEST_ID) {
        url.setUrl(getServerUrl() + URL_SERIES + URL_LATEST);
    }
    else if (libraryId == MasterController::SERIES_UPDATED_ID) {
        url.setUrl(getServerUrl() + URL_SERIES + URL_SERIES_UPDATED);
    }
    else {
        url.setUrl(getServerUrl() + URL_SERIES);
    }
    QUrlQuery query;
    query.addQueryItem("size", "40");
    // only works if library id is always positive, should check this
    if (libraryId > MasterController::DEFAULT_LIBRARY_ID) {
        query.addQueryItem("library_id", libraryId);
    }
    if (page != 0) {
        query.addQueryItem("page", QString::number(page));
    }
    url.setQuery(query);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getCollectionSeries(QString collectionId, int page)
{
    qDebug() << "fetching series for collection " << collectionId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesReason));
    QUrl url;
    url.setUrl(getServerUrl() + URL_COLLECTIONS + "/" + collectionId + URL_SERIES);
    QUrlQuery query;
    query.addQueryItem("size", "40");
    if (page != 0) {
        query.addQueryItem("page", QString::number(page));
    }
    url.setQuery(query);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getSeriesCollections(QString seriesId)
{
    qDebug() << "fetching collections for series " << seriesId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesCollections));
    QUrl url;
    url.setUrl(getServerUrl() + URL_SERIES + "/" + seriesId + URL_COLLECTIONS);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::doSearch(const QString &searchTerm, qint64 timestamp) {
    searchSeries(searchTerm, timestamp);
    searchBooks(searchTerm, timestamp);
    searchCollections(searchTerm, timestamp);
}

void Komga_api::updateProgress(QString bookId, int page, bool completed)
{
    QJsonObject obj;
    if (completed) {
        obj.insert("completed", true);
    }
    else {
        obj.insert("page", page);
    }
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Progress));
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + bookId + "/" + URL_PROGRESS);
    r.setUrl(url);
    r.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json; charset=utf8");
    if (! completed && page == 0) {
        manager->deleteResource(r);
    }
    else {
        QJsonDocument doc{obj};
        qDebug() << doc.toJson(QJsonDocument::JsonFormat::Compact);
        manager->sendCustomRequest(r, "PATCH", doc.toJson(QJsonDocument::JsonFormat::Compact));
    }
}

void Komga_api::updateSeriesProgress(QString seriesId, bool completed)
{
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Progress));
    QUrl url;
    url.setUrl(getServerUrl() + URL_SERIES + "/" + seriesId + "/" + URL_PROGRESS);
    r.setUrl(url);
    if (completed) {
        manager->post(r, QByteArray{});
    }
    else {
        manager->deleteResource(r);
    }
}

void Komga_api::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    QString msg = "";
    for (QSslError er : errors) {
        msg += er.errorString();
        msg += " ";
        msg += er.error();
        msg += "; ";
    }
    qWarning() << "[net] SSL Errors: " << msg;
    emit networkErrorHappened("[net] SSL Errors: " + msg);
}

void Komga_api::searchSeries(const QString &searchTerm, qint64 timestamp) {
    qDebug() << "search series for " << searchTerm;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesSearch));
    QUrl url;
    url.setUrl(getServerUrl() + URL_SERIES);
    QUrlQuery query;
    query.addQueryItem("size", "10");
    query.addQueryItem("search", searchTerm);
    url.setQuery(query);
    r.setUrl(url);

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, [=](){
        m_searchMapper->map(reply);
    });
    QString key = QString::number(timestamp) + URL_SERIES;
    m_replies.insert(key, reply);
    m_searchMapper->setMapping(reply, key);
}

void Komga_api::searchCollections(const QString &searchTerm, qint64 timestamp) {
    qDebug() << "search collections for " << searchTerm;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::CollectionsSearch));
    QUrl url;
    url.setUrl(getServerUrl() + URL_COLLECTIONS);
    QUrlQuery query;
    query.addQueryItem("size", "10");
    query.addQueryItem("search", searchTerm);
    url.setQuery(query);
    r.setUrl(url);

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, [=](){
        m_searchMapper->map(reply);
    });
    QString key = QString::number(timestamp) + URL_COLLECTIONS;
    m_replies.insert(key, reply);
    m_searchMapper->setMapping(reply, key);
}

void Komga_api::searchBooks(const QString &searchTerm, qint64 timestamp) {
    qDebug() << "search books for " << searchTerm;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::BooksSearch));
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS);
    QUrlQuery query;
    query.addQueryItem("size", "10");
    query.addQueryItem("search", searchTerm);
    url.setQuery(query);
    r.setUrl(url);

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, [=](){
        m_searchMapper->map(reply);
    });
    QString key = QString::number(timestamp) + URL_BOOKS;
    m_replies.insert(key, reply);
    m_searchMapper->setMapping(reply, key);
}

void Komga_api::getBooks(QString seriesId, int page) {
    qDebug() << "fetch books for series " << seriesId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Books));
    QUrl url;
    QUrlQuery query;
    if (seriesId == MasterController::BOOKS_LATEST_ID) {
        url.setUrl(getServerUrl() + URL_BOOKS + URL_LATEST);
    }
    else if (seriesId == MasterController::BOOKS_ON_DECK_ID) {
        url.setUrl(getServerUrl() + URL_BOOKS + URL_ONDECK);
    }
    else if (seriesId == MasterController::BOOKS_READING_ID) {
        url.setUrl(getServerUrl() + URL_BOOKS);
        query.addQueryItem("read_status", "IN_PROGRESS");
        query.addQueryItem("sort", "readProgress.lastModified,desc");
    }
    else {
        url.setUrl(getServerUrl() + URL_SERIES + "/" + seriesId + URL_BOOKS);
    }
    query.addQueryItem("size", "40");
    if (page != 0) {
        query.addQueryItem("page", QString::number(page, 10));
    }
    url.setQuery(query);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::apiReplyFinished(QNetworkReply *reply) {
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        int reason = reply->request().attribute(QNetworkRequest::Attribute::User).toInt();
        QByteArray response(reply->readAll());
        QJsonDocument doc = QJsonDocument::fromJson( response);
//        qDebug() << doc;
        if (reason == RequestReason::Libraries) {
            emit libraryDataReady(doc);
        }
        else if (reason == RequestReason::SeriesReason) {
            QJsonObject page = doc.object();
            emit seriesDataReady(page);
        }
        else if (reason == RequestReason::Books) {
            QJsonObject page = doc.object();
            emit booksDataReady(page);
        }
        else if (reason == RequestReason::Collections) {
            QJsonObject page = doc.object();
            emit collectionsDataReady(page);
        }
        else if (reason == RequestReason::Progress) {
            qDebug() << "progress response " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        }
        else if (reason == RequestReason::SeriesCollections) {
            QJsonArray list = doc.array();
            emit seriesCollectionsDataReady(list);
        }
        else if (reason == RequestReason::PreviousBook) {
            QJsonObject book = doc.object();
            emit previousBookReady(book);
        }
        else if (reason == RequestReason::NextBook) {
            QJsonObject book = doc.object();
            emit nextBookReady(book);
        }
    }
    // else emit an error event
    else {
        qWarning() << "[net] ERROR " << reply->errorString() << " code " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        emit networkErrorHappened("[net] ERROR " + reply->errorString());
    }
}

void Komga_api::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "[net] authentication";
    QSettings settings;
    settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
    QString user = settings.value(Komga_api::SETTINGS_KEY_SERVER_USER).toString();
    QString pw = settings.value(Komga_api::SETTINGS_KEY_SERVER_PASSWORD).toString();
    settings.endGroup();
    authenticator->setUser(user);
    authenticator->setPassword(pw);
}
QByteArray Komga_api::getThumbnail(int id, Komga_api::ThumbnailType type) {
    qDebug() << "fetching thumbnail for id " << id;
    QNetworkRequest r;
    QUrl url;
    if (type == ThumbnailType::BookThumbnail) {
        url.setUrl(getServerUrl() + URL_BOOKS + "/" + QString::number(id, 10) + URL_THUMBNAILS);
    }
    else if (type == ThumbnailType::SeriesThumbnail) {
        url.setUrl(getServerUrl() + URL_SERIES + "/" + QString::number(id, 10) + URL_THUMBNAILS);
    }
    r.setUrl(url);
    QEventLoop eventLoop;

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    int retCode = eventLoop.exec();
    reply->deleteLater();
    if (retCode == 0 && reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    }
    else {
        qWarning() << "[net] error fetching thumbnail " << reply->errorString();
        return QByteArray();
    }
}
QNetworkRequest Komga_api::getThumbnailAsync(QString id) {
//    qDebug() << "fetch thumbnail async for id " << id;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Thumbnail));
    QUrl url;
    QStringList parts = id.split("/");
    QString thumbId = parts.at(1);
    QString type = parts.at(0);
    if (type == "book") {
        url.setUrl(getServerUrl() + URL_BOOKS + "/" + thumbId + URL_THUMBNAILS);
    }
    else if (type == "series") {
        url.setUrl(getServerUrl() + URL_SERIES + "/" + thumbId + URL_THUMBNAILS);
    }
    else if (type == "collection") {
        url.setUrl(getServerUrl() + URL_COLLECTIONS + "/" + thumbId + URL_THUMBNAILS);
    }
    r.setUrl(url);
    return r;
}
QByteArray Komga_api::getPage(QString id, int pageNum) {
    qDebug() << "fetch page num for id " << pageNum << "  " <<  id;
    QNetworkRequest r;
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + id + URL_PAGE + "/" + QString::number(pageNum, 10));
    QUrlQuery query;
    query.addQueryItem("zero_based", "true");
    url.setQuery(query);
    r.setUrl(url);
    QEventLoop eventLoop;

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    int retCode = eventLoop.exec();
    reply->deleteLater();
    if (retCode == 0 && reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    }
    else {
        qWarning() << "[net] error fetching page " << reply->errorString();
        return QByteArray();
    }
}
void Komga_api::getPageAsync(QString id, int pageNum) {
    qDebug() << "fetch page async num for id " << pageNum << "  " <<  id;
    QNetworkRequest r;
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + id + URL_PAGE + "/" + QString::number(pageNum, 10));
    QUrlQuery query;
    query.addQueryItem("zero_based", "true");
    url.setQuery(query);
    r.setUrl(url);

    QNetworkReply* reply = thumbnailsManager->get(r);
    connect(reply, &QNetworkReply::finished, [=](){
        m_mapper->map(reply);
    });
    QString key = id + "/" + QString::number(pageNum);
    m_replies.insert(key, reply);
    m_mapper->setMapping(reply, key);
}
QString Komga_api::getServerUrl() {
    QSettings settings;
    settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
    QString url = settings.value(Komga_api::SETTINGS_KEY_SERVER_URL).toString();
    settings.endGroup();
    if (! url.endsWith("/")) {
        return url + "/api/v1";
    }
    else {
        return url + "api/v1";
    }
}
