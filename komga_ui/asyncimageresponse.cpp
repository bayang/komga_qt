#include "asyncimageresponse.h"
#include <QNetworkReply>
#include <QSettings>

AsyncImageResponse::AsyncImageResponse(const QString &id, const QSize &requestedSize, Komga_api *api) :
    m_requestedSize{requestedSize}, m_api{api}, m_id{id}

{
    qDebug() << "start runnable ";
//    connect(&m_manager, &QNetworkAccessManager::authenticationRequired,
//            this, &AsyncImageResponse::authenticate);
    connect(&m_manager, &QNetworkAccessManager::authenticationRequired, [=](QNetworkReply *reply, QAuthenticator *authenticator){
        Q_UNUSED(reply);
        qDebug() << "authenticate async";
        QSettings settings;
        settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
        QString user = settings.value(Komga_api::SETTINGS_KEY_SERVER_USER).toString();
        QString pw = settings.value(Komga_api::SETTINGS_KEY_SERVER_PASSWORD).toString();
        settings.endGroup();
        authenticator->setUser(user);
        authenticator->setPassword(pw);
    });
    connect(&m_manager, &QNetworkAccessManager::finished, this, &AsyncImageResponse::handleDone);
    m_manager.get(m_api->getThumbnailAsync(id));
}
QQuickTextureFactory* AsyncImageResponse::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(m_image);
}
void AsyncImageResponse::handleDone(QNetworkReply *reply) {
    qDebug() << "handle done " << m_requestedSize;
    QImage i;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray ba = reply->readAll();
        i.loadFromData(ba);
        if (m_requestedSize.height() != -1) {
            if (m_requestedSize.width() != -1) {
                i = i.scaled(m_requestedSize.width(), m_requestedSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
            }
            else {
                i = i.scaledToHeight(m_requestedSize.height());
            }
        }
        m_image = i;
        qDebug() << "handle done im " << m_image.height() << " " << m_image.width();
        reply->deleteLater();
        emit finished();
    }
    else {
        qDebug() << "ERROR " << reply->errorString();
        m_image = i;
        reply->deleteLater();
        emit finished();
    }
}
void AsyncImageResponse::authenticate(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);
    qDebug() << "authenticate async";
    QSettings settings;
    settings.beginGroup(Komga_api::SETTINGS_SECTION_SERVER);
    QString user = settings.value(Komga_api::SETTINGS_KEY_SERVER_USER).toString();
    QString pw = settings.value(Komga_api::SETTINGS_KEY_SERVER_PASSWORD).toString();
    settings.endGroup();
    authenticator->setUser(user);
    authenticator->setPassword(pw);
}
