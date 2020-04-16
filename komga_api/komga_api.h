#ifndef KOMGA_API_H
#define KOMGA_API_H

#include <QList>
#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QJsonObject>
#include <QJsonDocument>
#include "komga_api_global.h"
#include "library.h"
#include "book.h"
#include "series.h"

class KOMGA_API_EXPORT Komga_api: public QObject
{
    Q_OBJECT
public:
    Komga_api(QObject *parent = nullptr);
    void getLibraries();
    void getSeries(int libraryId, int page = 0);
    void getBooks(int seriesId, int page = 0);
    static const QString BASE_URL;
    static const QString URL_LIBRARIES;
    static const QString URL_SERIES;
    static const QString URL_BOOKS;
    static const QString URL_THUMBNAILS;
    static const QString URL_PAGE;
    enum RequestReason {
        Libraries = QNetworkRequest::Attribute::User + 1,
        SeriesReason = QNetworkRequest::Attribute::User + 2,
        Books = QNetworkRequest::Attribute::User + 3
    };
    enum ThumbnailType {
        SeriesThumbnail,
        BookThumbnail
    };
    QByteArray getThumbnail(int id, ThumbnailType type);
    QByteArray getPage(int id, int pageNum);


private:
    QNetworkAccessManager* manager = nullptr;
    QNetworkAccessManager* thumbnailsManager = nullptr;
//    QNetworkReply* apiReply;
    void authenticate(QNetworkReply *reply, QAuthenticator *authenticator);
    void apiReplyFinished(QNetworkReply *reply);

signals:
    void libraryDataReady(QJsonDocument libraries);
    void seriesDataReady(QJsonObject series);
    void booksDataReady(QJsonObject books);
};

#endif // KOMGA_API_H
