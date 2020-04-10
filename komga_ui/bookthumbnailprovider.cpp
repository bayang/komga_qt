#include "bookthumbnailprovider.h"

BookThumbnailProvider::BookThumbnailProvider(BookModel* model) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), bookModel(model)
{

}
QPixmap BookThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    qDebug() << "id" << id;
    QByteArray a = bookModel->getThumbnail(id.toInt());
    if (a.isNull() || a.isEmpty()) {
        qDebug() << "is null or empty";
        return QPixmap(":/gray.png");
    }
    QPixmap pic;
    pic.loadFromData(a);
    size->setWidth(pic.width());
    size->setHeight(pic.height());
    if (requestedSize.height() != -1) {
        if (requestedSize.width() != -1) {
            return pic.scaled(requestedSize.width(), requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
        }
        return pic.scaledToHeight(requestedSize.height());
    }
    return pic;
}
