#include "library.h"

Library::Library(QObject *parent):
    QObject{parent}
{

}
QString Library::name() const {
    return m_name;
}

QString Library::root() const {
    return m_root;
}
QString Library::id() const {
    return m_id;
}

void Library::setName(const QString &name) {
    m_name = name;
}

void Library::setRoot(const QString &root) {
    m_root = root;
}

void Library::setId(QString id) {
    m_id = id;
}
