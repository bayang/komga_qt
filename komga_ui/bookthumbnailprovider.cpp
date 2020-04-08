#include "bookthumbnailprovider.h"

BookThumbnailProvider::BookThumbnailProvider(BookModel* model) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), bookModel(model)
{

}
QPixmap BookThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    QByteArray a = bookModel->getThumbnail(id.toInt());
    QPixmap pic;
    pic.loadFromData(a);
    return pic;
}
