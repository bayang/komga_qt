#include "bookpageprovider.h"

BookPageProvider::BookPageProvider(BookModel* model) :
    QQuickImageProvider(QQuickImageProvider::Image), bookModel(model)
{

}
QImage BookPageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    Q_UNUSED(requestedSize);
    QStringList parts = id.split("/");
    int idNb = parts.at(0).toInt();
    int pageNb = parts.at(1).toInt();

    bookModel->preloadPage(idNb, pageNb + 1);
    if (QByteArray* c = bookModel->getImageFromCache(id)) {
        QImage pic;
        pic.loadFromData(*c);
        *size = QSize(pic.width(), pic.height());
        return pic;
    }
    else {
        QByteArray a = bookModel->getPage(idNb, pageNb);
        if (a.isNull() || a.isEmpty()) {
            QImage pix;

            pix.fill(QColor("gray"));
            qWarning() << "page is null or empty " << idNb << " " << pageNb;
            return pix;
        }
        QImage pic;
        pic.loadFromData(a);
        *size = QSize(pic.width(), pic.height());
        return pic;
    }
}
