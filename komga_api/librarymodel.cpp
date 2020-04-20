#include "librarymodel.h"
#include <QJsonArray>

LibraryModel::LibraryModel(QObject *parent, Komga_api* api) :
    QAbstractListModel{parent}, m_api{api}, m_libraries{}
{
    connect(m_api, &Komga_api::libraryDataReady,
            this, &LibraryModel::apiDataReceived);
}

void LibraryModel::apiDataReceived(QJsonDocument libraries) {
    emit beginResetModel();
    qDeleteAll(m_libraries);
    m_libraries.clear();
    emit endResetModel();
    QJsonArray array = libraries.array();
    emit layoutAboutToBeChanged();
    foreach (const QJsonValue &value, array) {
        Library* l = new Library(this);
        QJsonObject jsob = value.toObject();
        qDebug() << jsob["id"].toInt();
        qDebug() << jsob["name"].toString();
        l->setId(jsob["id"].toInt());
        l->setName(jsob["name"].toString());
        l->setRoot(jsob["root"].toString());
        m_libraries.append(std::move(l));
    }
    emit layoutChanged();
}
int LibraryModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_libraries.size();
}
QHash<int, QByteArray> LibraryModel::roleNames() const {
    QHash<int, QByteArray> roles;
        roles[IdRole] = "libraryId";
        roles[NameRole] = "libraryName";
        roles[RootRole] = "libraryRoot";
        roles[ObjectRole] = "libraryObject";
        return roles;
}
QVariant LibraryModel::data(const QModelIndex &index, int role) const {
    if (! index.isValid()) {
        qDebug() << "invalid indx " << index.row();
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_libraries.count())
        return QVariant();

    const Library* library = m_libraries[index.row()];
    if (library) {
        if (role == NameRole)
            return library->name();
        else if (role == IdRole)
            return library->id();
        else if (role == RootRole)
            return library->root();
        else if (role == ObjectRole)
            qDebug() << library->name();
        return library;
    }
    return QVariant();
}
void LibraryModel::fetchData() {
    m_api -> getLibraries();
}
//Library* LibraryModel::get(int index) const {
//    if (index < 0 || index > m_libraries.count()) {

//    }
//    return m_libraries.at(index);
//}
