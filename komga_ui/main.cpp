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
#include "bookpageprovider.h"
#include "networkinformer.h"
#include "asyncimageprovider.h"
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(":/assets/favicon.ico"));
//    QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    QQuickStyle::setStyle(QStringLiteral("Universal"));
    QQuickStyle::setFallbackStyle(QStringLiteral("Material"));
    app.setOrganizationName("bayang");
    app.setOrganizationDomain("bayang.github.com");
    app.setApplicationName("Komga-ui");

    Komga_api *api = new Komga_api(&app);
    LibraryModel *lm = new LibraryModel(&app, api);
    SeriesModel *seriesmodel = new SeriesModel(&app, api);
    BookModel *bookModel = new BookModel(&app, api);
    NetworkInformer *informer = new NetworkInformer(&app, api);
    MasterController* controller = new MasterController{seriesmodel, bookModel, informer, &app};
    controller->setLibraryModel(lm);

    qmlRegisterType<Library>("komga_api", 1, 0,
    "Library");
    qmlRegisterType<Series>("komga_api", 1, 0,
    "Series");
    qmlRegisterType<Book>("komga_api", 1, 0,
    "Book");
    qmlRegisterType<BookMetadata>("komga_api", 1, 0,
    "BookMetadata");

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("controller",
    controller);
    engine.addImageProvider("page", new BookPageProvider(bookModel));
    engine.addImageProvider("async", new AsyncImageProvider(api));

    const QUrl url(QStringLiteral("qrc:/qml/masterview.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
