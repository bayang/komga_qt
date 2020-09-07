#ifndef READLIST_H
#define READLIST_H

#include "komga_api_global.h"
#include <QObject>

class KOMGA_API_EXPORT ReadList : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString ui_readListId READ id WRITE setId NOTIFY idChanged )
    Q_PROPERTY( QString ui_readListName READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY( bool ui_readListFiltered READ filtered WRITE setFiltered NOTIFY filteredChanged )
    Q_PROPERTY( QList<QString> ui_readListBooks READ booksIds WRITE setBooksIds NOTIFY booksChanged )
    Q_PROPERTY( int ui_readListBooksSize READ booksIdsSize NOTIFY booksSizeChanged )

public:
    explicit ReadList(QObject *parent = nullptr);
    QString id() const;
    void setId(QString id);

    QString name() const;
    void setName(const QString &name);

    bool filtered() const;
    void setFiltered(bool filtered);

    QList<QString> booksIds() const;
    void setBooksIds(const QList<QString> &booksIds);

    int booksIdsSize();

signals:
    void idChanged(QString id);
    void nameChanged(QString name);
    void orderedChanged(bool ordered);
    void filteredChanged(bool filtered);
    void booksChanged(QList<int> booksIds);
    void booksSizeChanged(int booksIdsSize);


private:
    QString m_id{};
    QString m_name{};
    bool m_ordered{false};
    bool m_filtered{false};
    QList<QString> m_booksIds{};

};

#endif // READLIST_H
