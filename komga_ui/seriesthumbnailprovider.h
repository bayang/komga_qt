#ifndef SERIESTHUMBNAILPROVIDER_H
#define SERIESTHUMBNAILPROVIDER_H

#include <QQuickImageProvider>
#include "seriesmodel.h"

class SeriesThumbnailProvider : public QQuickImageProvider
{
public:
    SeriesThumbnailProvider(SeriesModel* model);

    // QQuickImageProvider interface
public:
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    SeriesModel* seriesModel = nullptr;
};

#endif // SERIESTHUMBNAILPROVIDER_H
