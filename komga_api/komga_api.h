#ifndef KOMGA_API_H
#define KOMGA_API_H

#include <QList>
#include <QCache>
#include <QNetworkAccessManager>
#include <QSignalMapper>
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
    static const QString URL_LIBRARIES;
    static const QString URL_SERIES;
    static const QString URL_SERIES_LATEST;
    static const QString URL_SERIES_NEW;
    static const QString URL_SERIES_UPDATED;
    static const QString URL_BOOKS;
    static const QString URL_THUMBNAILS;
    static const QString URL_PAGE;
    static const QString URL_PROGRESS;
    static const QString SETTINGS_SECTION_SERVER;
    static const QString SETTINGS_KEY_SERVER_URL;
    static const QString SETTINGS_KEY_SERVER_USER;
    static const QString SETTINGS_KEY_SERVER_PASSWORD;

    enum RequestReason {
        Libraries = QNetworkRequest::Attribute::User + 1,
        SeriesReason = QNetworkRequest::Attribute::User + 2,
        Books = QNetworkRequest::Attribute::User + 3,
        Thumbnail = QNetworkRequest::Attribute::User + 4,
        SeriesSearch = QNetworkRequest::Attribute::User + 5,
        BooksSearch = QNetworkRequest::Attribute::User + 6,
        Progress = QNetworkRequest::Attribute::User + 7,
    };
    enum ThumbnailType {
        SeriesThumbnail,
        BookThumbnail
    };
    QByteArray getThumbnail(int id, ThumbnailType type);
    QNetworkRequest getThumbnailAsync(QString id);
    QByteArray getPage(int id, int pageNum);
    void getPageAsync(int id, int pageNum);
    QString getServerUrl();
    void authenticate(QNetworkReply *reply, QAuthenticator *authenticator);
    void doSearch(const QString &searchTerm, qint64 timestamp);
    void updateProgress(int bookId, int page, bool completed = false);
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    QNetworkAccessManager* manager = nullptr;
    QNetworkAccessManager* thumbnailsManager = nullptr;
    void apiReplyFinished(QNetworkReply *reply);
    QSignalMapper* m_mapper = nullptr;
    QSignalMapper* m_searchMapper = nullptr;
    QHash<QString, QNetworkReply*> m_replies;
    void preloadImageReady(const QString &id);
    void searchDataReceived(const QString &id);
    void searchSeries(const QString &searchTerm, qint64 timestamp);
    void searchBooks(const QString &searchTerm, qint64 timestamp);

signals:
    void libraryDataReady(QJsonDocument libraries);
    void seriesDataReady(QJsonObject series);
    void booksDataReady(QJsonObject books);
    void netWorkAccessibleChanged(bool accessible);
    void networkErrorHappened(QString message);
    void preloadImageDataReady(QPair<QString, QByteArray> res);
    void searchSeriesDataReady(QPair<QString, QJsonDocument> res);
    void searchBookDataReady(QPair<QString, QJsonDocument> res);
};

#endif // KOMGA_API_H
