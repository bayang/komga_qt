#include "series.h"

Series::Series(QObject *parent):
    QObject{parent}
{

}

QString Series::name() const {
    return m_name;
}
int Series::id() const {
    return m_id;
}
int Series::libraryId() const {
    return m_libraryId;
}
QString Series::url() const {
    return m_url;
}
int Series::booksCount() const {
    return m_booksCount;
}
void Series::setName(QString name) {
    m_name = name;
}
void Series::setUrl(QString url) {
    m_url = url;
}
void Series::setId(int id) {
    m_id = id;
}
void Series::setLibraryId(int id) {
    m_libraryId = id;
}
void Series::setBooksCount(int count) {
    m_booksCount = count;
}

QString Series::metadataStatus() const
{
    return m_metadataStatus;
}

void Series::setMetadataStatus(const QString &metadataStatus)
{
    m_metadataStatus = metadataStatus;
}

QString Series::metadataTitle() const
{
    return m_metadataTitle;
}

void Series::setMetadataTitle(const QString &metadataTitle)
{
    m_metadataTitle = metadataTitle;
}
