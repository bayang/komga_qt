#include "komga_api.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QVariant>
#include <QEventLoop>
#include "mastercontroller.h"

const QString Komga_api::BASE_URL{"http://localhost:8080/komga/api/v1"};
//const QString Komga_api::BASE_URL{"http://192.168.1.18:12080/api/v1"};
const QString Komga_api::URL_LIBRARIES{"/libraries"};
const QString Komga_api::URL_SERIES{"/series"};
const QString Komga_api::URL_BOOKS{"/books"};
const QString Komga_api::URL_THUMBNAILS{"/thumbnail"};
const QString Komga_api::URL_PAGE{"/pages"};

Komga_api::Komga_api(QObject *parent):
    QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    thumbnailsManager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Komga_api::apiReplyFinished);
    connect(manager, &QNetworkAccessManager::authenticationRequired,
            this, &Komga_api::authenticate);
    connect(thumbnailsManager, &QNetworkAccessManager::authenticationRequired,
            this, &Komga_api::authenticate);
}

void Komga_api::getLibraries() {
    qDebug() << "fetch libraries";
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Libraries));
    QUrl url;
    url.setUrl(BASE_URL + URL_LIBRARIES);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getSeries(int libraryId, int page) {
    qDebug() << "fetch series for library " << libraryId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesReason));
    QUrl url;
    url.setUrl(BASE_URL + URL_SERIES);
    QUrlQuery query;
    query.addQueryItem("size", "30");
    if (libraryId != MasterController::DEFAULT_LIBRARY_ID) {
        query.addQueryItem("library_id", QString::number(libraryId));
    }
    if (page != 0) {
        query.addQueryItem("page", QString::number(page));
    }
    url.setQuery(query);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getBooks(int seriesId, int page) {
    qDebug() << "fetch books for series " << seriesId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Books));
    QUrl url;
    url.setUrl(BASE_URL + URL_SERIES + "/" + QString::number(seriesId, 10) + URL_BOOKS);
    QUrlQuery query;
    query.addQueryItem("size", "20");
    if (page != 0) {
        qDebug() << " page " << page;
        query.addQueryItem("page", QString::number(page, 10));
    }
    url.setQuery(query);
    qDebug() << " url " << url;
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::apiReplyFinished(QNetworkReply *reply) {
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        int reason = reply->request().attribute(QNetworkRequest::Attribute::User).toInt();
        QByteArray response(reply->readAll());
        QJsonDocument doc = QJsonDocument::fromJson( response);
        qDebug() << doc;
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
    }
    // else emit an error event
    else {
        qDebug() << "ERROR " << reply->errorString();
    }
}

void Komga_api::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "authenticate";
    authenticator->setUser("admin@example.org");
    authenticator->setPassword("EiwKPj1yR2MO");
//    authenticator->setPassword("TttroYQv0vNb");
}
QByteArray Komga_api::getThumbnail(int id, Komga_api::ThumbnailType type) {
    qDebug() << "fetch thumbnail for id " << id;
    QNetworkRequest r;
    QUrl url;
    if (type == ThumbnailType::BookThumbnail) {
        url.setUrl(BASE_URL + URL_BOOKS + "/" + QString::number(id, 10) + URL_THUMBNAILS);
    }
    else if (type == ThumbnailType::SeriesThumbnail) {
        url.setUrl(BASE_URL + URL_SERIES + "/" + QString::number(id, 10) + URL_THUMBNAILS);
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
        qDebug() << "error fetching thumbnail " << reply->errorString();
        return QByteArray();
    }
}
QByteArray Komga_api::getPage(int id, int pageNum) {
    qDebug() << "fetch page num for id " << pageNum << "  " <<  id;
    QNetworkRequest r;
    QUrl url;
    url.setUrl(BASE_URL + URL_BOOKS + "/" + QString::number(id, 10) + URL_PAGE + "/" + QString::number(pageNum, 10));
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
        qDebug() << "error fetching page " << reply->errorString();
        return QByteArray();
    }
}
