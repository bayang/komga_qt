#include "searchmodel.h"

SearchModel::SearchModel(QObject *parent, Komga_api* api) :
   QAbstractListModel{parent}, m_api{api}, m_results{}
{

}
int SearchModel::rowCount(const QModelIndex &parent) const {
    Q_ASSERT(checkIndex(parent));
    if (parent.isValid()) {
        return 0;
    }
    return m_results.count();
}
QVariant SearchModel::data(const QModelIndex &index, int role) const {
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));
    if (! index.isValid()) {
        qDebug() << "invalid indx " << index.row();
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_results.count())
        return QVariant();

    const SearchResult* result = m_results[index.row()];
    if (role == NameRole)
        return result->name();
    else if (role == IdRole)
        return result->id();
    else if (role == ResultTypeRole)
        return result->resultType();
    return QVariant();
}
QHash<int, QByteArray> SearchModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "bookId";
        roles[NameRole] = "bookName";
        roles[ResultTypeRole] = "resultType";
        return roles;
}
