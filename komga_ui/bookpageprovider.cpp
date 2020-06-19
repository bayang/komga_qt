#include "bookpageprovider.h"

BookPageProvider::BookPageProvider(MasterController* controller) :
    QQuickImageProvider(QQuickImageProvider::Image), m_controller(controller)
{

}
QImage BookPageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    Q_UNUSED(requestedSize);
    QStringList parts = id.split("/");
    int idNb = parts.at(0).toInt();
    int pageNb = parts.at(1).toInt();

    m_controller->preloadBookPages(idNb, pageNb);
    if (QByteArray* c = m_controller->getBookModel()->getImageFromCache(id)) {
        QImage pic;
        pic.loadFromData(*c);
        *size = QSize(pic.width(), pic.height());
        return pic;
    }
    else {
        QByteArray a = m_controller->getBookModel()->getPage(idNb, pageNb);
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
