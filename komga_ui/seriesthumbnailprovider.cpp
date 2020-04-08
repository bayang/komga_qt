#include "seriesthumbnailprovider.h"

SeriesThumbnailProvider::SeriesThumbnailProvider(SeriesModel* model) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), seriesModel(model)
{

}
QPixmap SeriesThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QByteArray a = seriesModel->getThumbnail(id.toInt());
    QPixmap pic;
    pic.loadFromData(a);
    size->setWidth(pic.width());
    size->setHeight(pic.height());
    if (requestedSize.height() != -1) {
        return pic.scaled(requestedSize.width(), requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
    }
    return pic;
}
