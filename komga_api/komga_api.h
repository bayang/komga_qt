#ifndef KOMGA_API_H
#define KOMGA_API_H

#include "komga_api_global.h"
#include "library.h"
#include "book.h"
#include "series.h"
#include "seriesfilter.h"
#include <QList>
#include <QCache>
#include <QNetworkAccessManager>
#include <QSignalMapper>
#include <QObject>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHash>


class KOMGA_API_EXPORT Komga_api: public QObject
{
    Q_OBJECT
public:
    Komga_api(QObject *parent = nullptr);
    void getLibraries();
    void getSeries(QString libraryId, int page = 0);
    void filterSeries(QString libraryId, SeriesFilter* filters, int page = 0);
    void getCollectionSeries(QString collectionId, int page = 0);
    void getSeriesCollections(QString seriesId);
    void getBooks(QString seriesId, int page = 0);
    void getReadListBooks(QString readListId, int page = 0);
    static const QString URL_LIBRARIES;
    static const QString URL_SERIES;
    static const QString URL_LATEST;
    static const QString URL_ONDECK;
    static const QString URL_SERIES_NEW;
    static const QString URL_SERIES_UPDATED;
    static const QString URL_BOOKS;
    static const QString URL_THUMBNAILS;
    static const QString URL_PAGE;
    static const QString URL_PROGRESS;
    static const QString URL_COLLECTIONS;
    static const QString URL_NEXT;
    static const QString URL_PREVIOUS;
    static const QString URL_READLISTS;
    static const QString URL_TAGS;
    static const QString URL_GENRES;
    static const QString URL_AGE_RATINGS;
    static const QString URL_LANGUAGES;
    static const QString URL_PUBLISHERS;
    static const QString KEY_LIBRARY;
    static const QString KEY_COLLECTION;
    static const QString KEY_SERIES;
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
        Collections = QNetworkRequest::Attribute::User + 8,
        SeriesCollections = QNetworkRequest::Attribute::User + 9,
        CollectionsSearch = QNetworkRequest::Attribute::User + 10,
        NextBook = QNetworkRequest::Attribute::User + 11,
        PreviousBook = QNetworkRequest::Attribute::User + 12,
        ReadLists = QNetworkRequest::Attribute::User + 13,
        ReadListsSearch = QNetworkRequest::Attribute::User + 14,
        Tags = QNetworkRequest::Attribute::User + 15,
        Genres = QNetworkRequest::Attribute::User + 16,
        AgeRatings = QNetworkRequest::Attribute::User + 17,
        Languages = QNetworkRequest::Attribute::User + 18,
        Publishers = QNetworkRequest::Attribute::User + 19,
    };
    enum ThumbnailType {
        SeriesThumbnail,
        BookThumbnail
    };
    enum ApiType {
        Series,
        Book
    };
    Q_ENUM(ApiType);
    QByteArray getThumbnail(int id, ThumbnailType type);
    QNetworkRequest getThumbnailAsync(QString id);
    QByteArray getPage(QString id, int pageNum);
    void getPageAsync(QString id, int pageNum);
    QString getServerUrl();
    void authenticate(QNetworkReply *reply, QAuthenticator *authenticator);
    void doSearch(const QString &searchTerm, qint64 timestamp);
    void updateProgress(QString bookId, int page, bool completed = false);
    void updateSeriesProgress(QString seriesId, bool completed = true);
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void getCollections(int page = 0);
    void getReadLists(int page = 0);
    void previousBook(QString bookId);
    void nextBook(QString bookId);
    void getTags(QHash<QString,QString> queryParams);
    void getGenres(QHash<QString,QString> queryParams);
    void getAgeRatings(QHash<QString,QString> queryParams);
    void getLanguages(QHash<QString,QString> queryParams);
    void getPublishers(QHash<QString,QString> queryParams);

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
    void searchCollections(const QString &searchTerm, qint64 timestamp);
    void searchReadLists(const QString &searchTerm, qint64 timestamp);

signals:
    void libraryDataReady(QJsonDocument libraries);
    void collectionsDataReady(QJsonObject page);
    void readListsDataReady(QJsonObject page);
    void seriesDataReady(QJsonObject series);
    void booksDataReady(QJsonObject books);
    void netWorkAccessibleChanged(bool accessible);
    void networkErrorHappened(QString message);
    void preloadImageDataReady(QPair<QString, QByteArray> res);
    void searchSeriesDataReady(QPair<QString, QJsonDocument> res);
    void searchBookDataReady(QPair<QString, QJsonDocument> res);
    void seriesCollectionsDataReady(QJsonArray list);
    void searchCollectionsDataReady(QPair<QString, QJsonDocument> res);
    void nextBookReady(QJsonObject book);
    void previousBookReady(QJsonObject book);
    void searchReadListsDataReady(QPair<QString, QJsonDocument> res);
    void tagsDataReady(QList<QString> tags);
    void genresDataReady(QList<QString> genres);
    void ageRatingsDataReady(QList<QString> ageRatings);
    void languagesDataReady(QList<QString> languages);
    void publishersDataReady(QList<QString> publishers);
};

#endif // KOMGA_API_H
