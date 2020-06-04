#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include "komga_api_global.h"
#include "komga_api.h"
#include <QAbstractListModel>
#include "searchresult.h"


class KOMGA_API_EXPORT SearchModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SearchModel(QObject *parent = nullptr, Komga_api *api = nullptr);
    enum ResultRoles {
        IdRole = Qt::UserRole + 1,
        ResultTypeRole = Qt::UserRole + 2,
        NameRole = Qt::UserRole + 3,
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void doSearch(const QString &searchTerm);

    qlonglong currentTimestamp() const;
    void setCurrentTimestamp(qlonglong currentTimestamp);
    SearchResult* at(int index);

private:
    Komga_api* m_api = nullptr;
    QList<SearchResult*> m_results{};
    qlonglong m_currentTimestamp{0};

public slots:
    void resetModel();
    void searchBookDataReceived(QPair<QString, QJsonDocument> res);
    void searchSeriesDataReceived(QPair<QString, QJsonDocument> res);
};

#endif // SEARCHMODEL_H
