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
int Library::id() const {
    return m_id;
}

void Library::setName(QString name) {
    m_name = name;
}

void Library::setRoot(QString root) {
    m_root = root;
}

void Library::setId(int id) {
    m_id = id;
}
