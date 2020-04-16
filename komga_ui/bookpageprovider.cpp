#include "bookpageprovider.h"

BookPageProvider::BookPageProvider(BookModel* model) :
    QQuickImageProvider(QQuickImageProvider::Image), bookModel(model)
{

}
QImage BookPageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    int defaultHeight = 230;
    int defaultWidth = 175;
    qDebug() << "id" << id;
    QStringList parts = id.split("/");

    QByteArray a = bookModel->getPage(parts.at(0).toInt(), parts.at(1).toInt());
    if (a.isNull() || a.isEmpty()) {
        QImage pix;

        pix.fill(QColor("gray"));
        qDebug() << "is null or empty";
        return pix;
    }
    QImage pic;
    pic.loadFromData(a);
    *size = QSize(pic.width(), pic.height());
//    if (requestedSize.height() != -1) {
//        if (requestedSize.width() != -1) {
//            return pic.scaled(requestedSize.width(), requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
//        }
//        return pic.scaledToHeight(requestedSize.height());
//    }
    return pic;
}
