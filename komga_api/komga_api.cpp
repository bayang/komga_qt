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

const QString Komga_api::URL_LIBRARIES{"/libraries"};
const QString Komga_api::URL_SERIES{"/series"};
const QString Komga_api::URL_BOOKS{"/books"};
const QString Komga_api::URL_THUMBNAILS{"/thumbnail"};
const QString Komga_api::URL_PAGE{"/pages"};
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
    thumbnailsManager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Komga_api::apiReplyFinished);
    connect(manager, &QNetworkAccessManager::authenticationRequired,
            this, &Komga_api::authenticate);
    connect(thumbnailsManager, &QNetworkAccessManager::authenticationRequired,
            this, &Komga_api::authenticate);
    connect(manager, &QNetworkAccessManager::networkAccessibleChanged, [this](QNetworkAccessManager::NetworkAccessibility accessible){
        qDebug() << "network available " << accessible;
        if (accessible == QNetworkAccessManager::NetworkAccessibility::NotAccessible) {
            emit netWorkAccessibleChanged(false);
        }
        else {
            emit netWorkAccessibleChanged(true);
        }
    });
}

void Komga_api::getLibraries() {
    qDebug() << "fetch libraries";
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Libraries));
    QUrl url;
    url.setUrl(getServerUrl() + URL_LIBRARIES);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getSeries(int libraryId, int page) {
    qDebug() << "fetch series for library " << libraryId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesReason));
    QUrl url;
    url.setUrl(getServerUrl() + URL_SERIES);
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
    url.setUrl(getServerUrl() + URL_SERIES + "/" + QString::number(seriesId, 10) + URL_BOOKS);
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
        emit networkErrorHappened("ERROR " + reply->errorString());
    }
}

void Komga_api::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "authenticate";
    QSettings settings;
    settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
    QString user = settings.value(Komga_api::SETTINGS_KEY_SERVER_USER).toString();
    QString pw = settings.value(Komga_api::SETTINGS_KEY_SERVER_PASSWORD).toString();
    settings.endGroup();

    authenticator->setUser(user);
    authenticator->setPassword(pw);
}
QByteArray Komga_api::getThumbnail(int id, Komga_api::ThumbnailType type) {
    qDebug() << "fetch thumbnail for id " << id;
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
        qDebug() << "error fetching thumbnail " << reply->errorString();
        return QByteArray();
    }
}
QByteArray Komga_api::getPage(int id, int pageNum) {
    qDebug() << "fetch page num for id " << pageNum << "  " <<  id;
    QNetworkRequest r;
    QUrl url;
    url.setUrl(getServerUrl() + URL_BOOKS + "/" + QString::number(id, 10) + URL_PAGE + "/" + QString::number(pageNum, 10));
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
QString Komga_api::getServerUrl() {
    QSettings settings;
    settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
    QString url = settings.value(Komga_api::SETTINGS_KEY_SERVER_URL).toString();
    settings.endGroup();
    if (! url.endsWith("/")) {
        return url;
    }
    else {
        return url;
    }
}
