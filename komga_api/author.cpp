#include "author.h"

Author::Author(QObject *parent):
    QObject{parent}
{

}

QString Author::name() const
{
    return m_name;
}

void Author::setName(const QString &name)
{
    m_name = name;
}

QString Author::role() const
{
    return m_role;
}

void Author::setRole(const QString &role)
{
    m_role = role;
}
