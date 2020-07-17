#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT Collection : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_collectionId READ id WRITE setId NOTIFY idChanged )
    Q_PROPERTY( QString ui_collectionName READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY( bool ui_collectionOrdered READ ordered WRITE setOrdered NOTIFY orderedChanged )
    Q_PROPERTY( bool ui_collectionFiltered READ filtered WRITE setFiltered NOTIFY filteredChanged )
    Q_PROPERTY( QList<QString> ui_collectionSeries READ seriesIds WRITE setSeriesIds NOTIFY seriesChanged )


public:
    explicit Collection(QObject *parent = nullptr);

    QString id() const;
    void setId(QString id);

    QString name() const;
    void setName(const QString &name);

    bool ordered() const;
    void setOrdered(bool ordered);

    bool filtered() const;
    void setFiltered(bool filtered);

    QList<QString> seriesIds() const;
    void setSeriesIds(const QList<QString> &seriesIds);

signals:
    void idChanged(QString id);
    void nameChanged(QString name);
    void orderedChanged(bool ordered);
    void filteredChanged(bool filtered);
    void seriesChanged(QList<int> seriesIds);


private:
    QString m_id{};
    QString m_name{};
    bool m_ordered{false};
    bool m_filtered{false};
    QList<QString> m_seriesIds{};
};

#endif // COLLECTION_H
