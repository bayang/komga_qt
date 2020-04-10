#include "seriesthumbnailprovider.h"

SeriesThumbnailProvider::SeriesThumbnailProvider(SeriesModel* model) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), seriesModel(model)
{

}
QPixmap SeriesThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QByteArray a = seriesModel->getThumbnail(id.toInt());
    int defaultSize = 100;
    if (a.isNull() || a.isEmpty()) {
        QPixmap pix(defaultSize, defaultSize);
        pix.fill(QColor("gray").rgba());
        qDebug() << "is null or empty";
        return pix;
    }
    QPixmap pic;
    pic.loadFromData(a);
    *size = QSize(pic.width(), pic.height());
//    size->setWidth(pic.width());
//    size->setHeight(pic.height());
    if (requestedSize.height() != -1) {
        return pic.scaled(requestedSize.width(), requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
    }
    return pic;
}
