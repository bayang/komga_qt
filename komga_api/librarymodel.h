#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>
#include "komga_api.h"
#include <QJsonDocument>

class KOMGA_API_EXPORT LibraryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LibraryModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum LibraryRoles {
        IdRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        RootRole = Qt::UserRole + 3,
        ObjectRole = Qt::UserRole + 4
    };

private slots:
    void apiDataReceived(QJsonDocument libraries);

private:
    Komga_api* m_api = nullptr;
    QList<Library*> m_libraries{};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void fetchData();
//    Q_INVOKABLE Library* get(int index) const;
};

#endif // LIBRARYMODEL_H
