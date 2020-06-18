#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT Author: public QObject
{
    Q_OBJECT
public:
    Author(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString role() const;
    void setRole(const QString &role);

private:
    QString m_name{};
    QString m_role{};
};

#endif // AUTHOR_H
