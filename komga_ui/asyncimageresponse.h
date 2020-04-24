#ifndef ASYNCIMAGERESPONSE_H
#define ASYNCIMAGERESPONSE_H

#include <QQuickImageResponse>
#include <QThreadPool>
#include "komga_api.h"
#include <QImage>

class AsyncImageResponse : public QQuickImageResponse
{
    Q_OBJECT
public:
    AsyncImageResponse(const QString &id, const QSize &requestedSize, Komga_api *api);
    QImage m_image;

public slots:
    void handleDone(QNetworkReply *reply);
    void authenticate(QNetworkReply *reply, QAuthenticator *authenticator);

    // QQuickImageResponse interface
public:
    QQuickTextureFactory *textureFactory() const override;

private:
    const QSize m_requestedSize;
    Komga_api* m_api;
    QString m_id;
    QNetworkAccessManager m_manager;
};

#endif // ASYNCIMAGERESPONSE_H
