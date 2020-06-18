#include "networkinformer.h"

NetworkInformer::NetworkInformer(QObject *parent, Komga_api* api) :
    QObject{parent}, m_api{api}
{
    connect(m_api, &Komga_api::netWorkAccessibleChanged, this, [this](bool accessible) {
        qDebug() << "network accessible " << accessible;
        if (accessible != m_netWorkAccessible) {
            this->setNetWorkAccessible(accessible);
            emit networkAccessibleChanged(accessible);
        }
    });
    connect(m_api, &Komga_api::networkErrorHappened, this, [this](QString error) {
        qWarning() << "[net] network error " << error;
        if (error != m_errorMessage) {
            this->setErrorMessage(error);
            emit errorMessageChanged(error);
        }
    });
}

bool NetworkInformer::netWorkAccessible() const
{
    return m_netWorkAccessible;
}

void NetworkInformer::setNetWorkAccessible(bool netWorkAccessible)
{
    m_netWorkAccessible = netWorkAccessible;
}

QString NetworkInformer::errorMessage() const
{
    return m_errorMessage;
}

void NetworkInformer::setErrorMessage(const QString &errorMessage)
{
    m_errorMessage = errorMessage;
}
