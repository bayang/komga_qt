#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "librarymodel.h"
#include "seriesmodel.h"
#include "bookmodel.h"
#include "searchmodel.h"
#include "mastercontroller.h"
#include "library.h"
#include "book.h"
#include "bookmetadata.h"
#include "author.h"
#include "bookpageprovider.h"
#include "networkinformer.h"
#include "asyncimageprovider.h"
#include <QQuickStyle>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include "KomgaConfig.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char *file = context.file ? context.file : "";
    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    switch (type) {
    case QtDebugMsg:
        txt += QString("[Debug] %1:%2-%3").arg(file).arg(context.line).arg(msg);
        break;
    case QtInfoMsg:
        txt += QString("[Info] %1:%2-%3").arg(file).arg(context.line).arg(msg);
        break;
    case QtWarningMsg:
        txt += QString("[Warn] %1:%2-%3").arg(file).arg(context.line).arg(msg);
        break;
    case QtCriticalMsg:
        txt += QString("[Critical] %1:%2-%3").arg(file).arg(context.line).arg(msg);
        break;
    case QtFatalMsg:
        txt += QString("[Fatal] %1:%2-%3").arg(file).arg(context.line).arg(msg);
        break;
    }
    QFile outFile("komga_qt.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QDebug deb{&outFile};
    deb << txt << endl;
}

int main(int argc, char *argv[])
{
    qDebug() << PROJECT_NAME << " version: " << PROJECT_VER << endl;
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(":/assets/favicon.ico"));
    QQuickStyle::setStyle(QStringLiteral("Material"));
    QQuickStyle::setFallbackStyle(QStringLiteral("Default"));
    app.setOrganizationName("bayang");
    app.setOrganizationDomain("bayang.github.com");
    app.setApplicationName("Komga-ui");

    qSetMessagePattern("[%{type}] %{time} (%{file}:%{line}) - %{message}");
    #if defined(Q_OS_WIN)
        qInstallMessageHandler(myMessageOutput);
    #elif defined(Q_OS_MACOS)
        qInstallMessageHandler(myMessageOutput);
    #endif

    Komga_api *api = new Komga_api(&app);
    LibraryModel *lm = new LibraryModel(&app, api);
    SeriesModel *seriesmodel = new SeriesModel(&app, api);
    BookModel *bookModel = new BookModel(&app, api);
    SearchModel *searchModel = new SearchModel(&app, api);
    NetworkInformer *informer = new NetworkInformer(&app, api);
    MasterController* controller = new MasterController{seriesmodel, bookModel, informer, &app};
    controller->setLibraryModel(lm);
    controller->setSearchModel(searchModel);

    qmlRegisterType<Library>("komga_api", 1, 0,
    "Library");
    qmlRegisterType<Series>("komga_api", 1, 0,
    "Series");
    qmlRegisterType<Book>("komga_api", 1, 0,
    "Book");
    qmlRegisterType<BookMetadata>("komga_api", 1, 0,
    "BookMetadata");
    qmlRegisterType<SearchResult>("komga_api", 1, 0,
    "SearchResult");
    qmlRegisterType<Author>("komga_api", 1, 0,
    "Author");

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("controller",
    controller);
    engine.rootContext()->setContextProperty("APP_VERSION",
    PROJECT_VER);
    engine.addImageProvider("page", new BookPageProvider(controller));
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
