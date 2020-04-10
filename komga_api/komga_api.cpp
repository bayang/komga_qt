#include "komga_api.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QVariant>
#include <QEventLoop>

const QString Komga_api::BASE_URL{"http://localhost:8080/komga/api/v1"};
const QString Komga_api::URL_LIBRARIES{"/libraries"};
const QString Komga_api::URL_SERIES{"/series"};
const QString Komga_api::URL_BOOKS{"/books"};
const QString Komga_api::URL_THUMBNAILS{"/thumbnail"};

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

void Komga_api::getSeries(int libraryId) {
    qDebug() << "fetch series for library " << libraryId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::SeriesReason));
    QUrl url;
    url.setUrl(BASE_URL + URL_SERIES);
    QUrlQuery query;
    query.addQueryItem("size", "30");
    if (libraryId != -1) {
        query.addQueryItem("library_id", QString::number(libraryId));
    }
    url.setQuery(query);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::getBooks(int seriesId) {
    qDebug() << "fetch books for series " << seriesId;
    QNetworkRequest r;
    r.setAttribute(QNetworkRequest::Attribute::User, QVariant(RequestReason::Books));
    QUrl url;
    url.setUrl(BASE_URL + URL_SERIES + "/" + QString::number(seriesId, 10) + URL_BOOKS);
    r.setUrl(url);
    manager->get(r);
}

void Komga_api::apiReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        int reason = reply->request().attribute(QNetworkRequest::Attribute::User).toInt();
        QByteArray response(reply->readAll());
        QJsonDocument doc = QJsonDocument::fromJson( response);
        qDebug() << doc;
        if (reason == RequestReason::Libraries) {
            QJsonArray array = doc.array();
            QList<Library*> libraries;
            foreach (const QJsonValue &value, array) {
                Library* l = new Library();
                QJsonObject jsob = value.toObject();
                qDebug() << jsob["id"].toInt();
                qDebug() << jsob["name"].toString();
                l->setId(jsob["id"].toInt());
                l->setName(jsob["name"].toString());
                l->setRoot(jsob["root"].toString());

                libraries.append(std::move(l));
            }
            emit libraryDataReady(libraries);
        }
        else if (reason == RequestReason::SeriesReason) {
            QJsonObject page = doc.object();
            QJsonArray content = page["content"].toArray();
            QList<Series*> series;
            foreach (const QJsonValue &value, content) {
                Series* s = new Series();
                QJsonObject jsob = value.toObject();
                qDebug() << jsob["id"].toInt();
                qDebug() << jsob["name"].toString();
                s->setId(jsob["id"].toInt());
                QString n = jsob["name"].toString();
//                s->setName(QString(jsob["name"].toString()));
                s->setName(n);
                s->setBooksCount(jsob["booksCount"].toInt());
                s->setLibraryId(jsob["libraryId"].toInt());
                QString u = jsob["url"].toString();
                s->setUrl(u);
                QJsonObject metadata = jsob["metadata"].toObject();
                s->setMetadataTitle(metadata["title"].toString());
                s->setMetadataStatus(metadata["status"].toString());
                series.append(std::move(s));
            }
            emit seriesDataReady(series);
        }
        else if (reason == RequestReason::Books) {
            QJsonObject page = doc.object();
            QJsonArray content = page["content"].toArray();
            QList<Book*> books;
            foreach (const QJsonValue &value, content) {
                Book* b = new Book();
                QJsonObject jsob = value.toObject();
                b->setId(jsob["id"].toInt());
                b->setSeriesId(jsob["seriesId"].toInt());
                b->setName(jsob["name"].toString());
                b->setUrl(jsob["url"].toString());
                b->setSizeBytes(jsob["sizeBytes"].toInt());
                b->setSize(jsob["size"].toString());
                b->setPagesCount(jsob["pagesCount"].toInt());
                QJsonObject media = jsob["media"].toObject();
                b->setMediaStatus(media["status"].toString());
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
                    aut.append(value.   toString());
                }
                meta->setAuthors(aut);
                b->setBookMetadata(meta);
                books.append(std::move(b));
            }
            emit booksDataReady(books);
        }
    }
    // else emit an error event
    else {
        qDebug() << "ERROR";
    }
    reply->deleteLater();
}

void Komga_api::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "authenticate";
    authenticator->setUser("admin@example.org");
    authenticator->setPassword("EiwKPj1yR2MO");
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
    eventLoop.exec();
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    }
    else {
        qDebug() << "error fetching thumbnail " << reply->errorString();
        return QByteArray();
    }
}
