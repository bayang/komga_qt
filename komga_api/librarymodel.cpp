#include "librarymodel.h"

LibraryModel::LibraryModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}, m_libraries{}
{
    connect(m_api, &Komga_api::libraryDataReady,
            this, &LibraryModel::apiDataReceived);
}
void LibraryModel::apiDataReceived(QList<Library*> libraries) {
    emit beginResetModel();
    m_libraries = std::move(libraries);
    emit endResetModel();
}
int LibraryModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_libraries.size();
}
QHash<int, QByteArray> LibraryModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "libraryId";
        roles[NameRole] = "libraryName";
        roles[RootRole] = "libraryRoot";
        return roles;
}
QVariant LibraryModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_libraries.count())
        return QVariant();

    const Library* library = m_libraries[index.row()];
    if (role == NameRole)
        return library->name();
    else if (role == IdRole)
        return library->id();
    else if (role == RootRole)
        return library->root();
    return QVariant();
}
void LibraryModel::fetchData() {
    m_api -> getLibraries();
}
Library* LibraryModel::get(int index) {
    return m_libraries.at(index);
}
