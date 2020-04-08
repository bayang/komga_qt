#ifndef BOOKTHUMBNAILPROVIDER_H
#define BOOKTHUMBNAILPROVIDER_H

#include <QQuickImageProvider>
#include "bookmodel.h"

class BookThumbnailProvider : public QQuickImageProvider
{
public:
    BookThumbnailProvider(BookModel* model);

    // QQuickImageProvider interface
public:
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    BookModel* bookModel;
};

#endif // BOOKTHUMBNAILPROVIDER_H
