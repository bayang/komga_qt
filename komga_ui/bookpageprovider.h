#ifndef BOOKPAGEPROVIDER_H
#define BOOKPAGEPROVIDER_H

#include <QQuickImageProvider>
#include "bookmodel.h"

class BookPageProvider : public QQuickImageProvider
{
public:
    BookPageProvider(BookModel* model);

public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    BookModel* bookModel = nullptr;
};

#endif // BOOKPAGEPROVIDER_H
