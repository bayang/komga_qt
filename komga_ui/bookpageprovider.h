#ifndef BOOKPAGEPROVIDER_H
#define BOOKPAGEPROVIDER_H

#include <QQuickImageProvider>
#include "bookmodel.h"
#include "mastercontroller.h"

class BookPageProvider : public QQuickImageProvider
{
public:
    BookPageProvider(MasterController* m_controller);

public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    MasterController* m_controller = nullptr;
};

#endif // BOOKPAGEPROVIDER_H
