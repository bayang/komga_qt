#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "librarymodel.h"
#include "seriesmodel.h"
#include "bookmodel.h"
#include "mastercontroller.h"
#include "library.h"
#include "book.h"
#include "bookmetadata.h"
#include "seriesthumbnailprovider.h"
#include "bookthumbnailprovider.h"
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(":/favicon.ico"));
    QQuickStyle::setStyle("Material");

    Komga_api *api = new Komga_api(&app);
    LibraryModel *lm = new LibraryModel(&app, api);
    SeriesModel *seriesmodel = new SeriesModel(&app, api);
    BookModel *bookModel = new BookModel(&app, api);
    MasterController controller;

    qmlRegisterType<Library>("komga_api", 1, 0,
    "Library");
    qmlRegisterType<Series>("komga_api", 1, 0,
    "Series");
    qmlRegisterType<Book>("komga_api", 1, 0,
    "Book");
    qmlRegisterType<BookMetadata>("komga_api", 1, 0,
    "BookMetadata");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("libraryModel",
    lm);
    engine.rootContext()->setContextProperty("seriesModel",
    seriesmodel);
    engine.rootContext()->setContextProperty("bookModel",
    bookModel);
    engine.rootContext()->setContextProperty("controller",
    &controller);
    engine.addImageProvider("series", new SeriesThumbnailProvider(seriesmodel));
    engine.addImageProvider("books", new BookThumbnailProvider(bookModel));

    const QUrl url(QStringLiteral("qrc:/masterview.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
