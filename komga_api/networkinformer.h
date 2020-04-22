#ifndef NETWORKINFORMER_H
#define NETWORKINFORMER_H

#include <QObject>
#include "komga_api_global.h"
#include "komga_api.h"

class KOMGA_API_EXPORT NetworkInformer : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool ui_networkAccessible READ netWorkAccessible WRITE setNetWorkAccessible NOTIFY networkAccessibleChanged )
    Q_PROPERTY( QString ui_networkError READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged )

public:
    explicit NetworkInformer(QObject *parent = nullptr, Komga_api *api = nullptr);

    bool netWorkAccessible() const;
    void setNetWorkAccessible(bool netWorkAccessible);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

private:
    Komga_api* m_api = nullptr;
    bool m_netWorkAccessible = true;
    QString m_errorMessage{""};

signals:
    void networkAccessibleChanged(bool accessible);
    void errorMessageChanged(QString errorMessage);

};

#endif // NETWORKINFORMER_H
