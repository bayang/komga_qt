#include "seriesthumbnailprovider.h"

SeriesThumbnailProvider::SeriesThumbnailProvider(SeriesModel* model) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), seriesModel(model)
{

}
QPixmap SeriesThumbnailProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QByteArray a = seriesModel->getThumbnail(id.toInt());
    int defaultHeight = 230;
    int defaultWidth = 175;
    if (a.isNull() || a.isEmpty()) {
        QPixmap pix(defaultWidth, defaultHeight);
        pix.fill(QColor("gray").rgba());
        qDebug() << "is null or empty";
        return pix;
    }
    QPixmap pic;
    pic.loadFromData(a);
    *size = QSize(pic.width(), pic.height());
    if (requestedSize.height() != -1) {
        if (requestedSize.width() != -1) {
            return pic.scaled(requestedSize.width(), requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
        }
        return pic.scaledToHeight(requestedSize.height());
    }
    return pic;
}
