#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT Library: public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_libraryName READ name WRITE setName )
    Q_PROPERTY( int ui_libraryId READ id WRITE setId)

public:
    Library(QObject *parent = nullptr);
    QString name() const;
    int id() const;
    QString root() const;
    void setName(const QString &name);
    void setRoot(const QString &root);
    void setId(int id);

private:
    int m_id{};
    QString m_name{};
    QString m_root{};
};

#endif // LIBRARY_H
