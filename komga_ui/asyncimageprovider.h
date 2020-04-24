#ifndef ASYNCIMAGEPROVIDER_H
#define ASYNCIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QThreadPool>
#include "komga_api.h"

class AsyncImageProvider : public QQuickAsyncImageProvider
{
public:
    AsyncImageProvider(Komga_api *api = nullptr);

    // QQuickAsyncImageProvider interface
public:
    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &requestedSize) override;

private:
    Komga_api* m_api = nullptr;
};

#endif // ASYNCIMAGEPROVIDER_H
