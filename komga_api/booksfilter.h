#ifndef BOOKSFILTER_H
#define BOOKSFILTER_H

#include <QObject>
#include <QVariantList>
#include "komga_api_global.h"

class KOMGA_API_EXPORT BooksFilter: public QObject
{
    Q_OBJECT
    Q_PROPERTY( QVariantList ui_booksFilterTags READ filterTags WRITE setFilterTags NOTIFY filterTagsChanged )

public:
    BooksFilter(QObject *parent = nullptr);
    void addTagFilter(QString &tag);
    void removeTagFilter(QString &tag);
    void addReadStatus(QString &status);
    void removeReadStatus(QString &status);

    QVariantList filterTags() const;
    void setFilterTags(const QVariantList &filterTags);

    QList<QString> appliedTags() const;

    QList<QString> filterReadStatuses() const;

signals:
    void filtersChanged();
    void filterTagsChanged(QVariantList tags);

private:
    QList<QString> m_filterTags{};
    QList<QString> m_appliedTags{};
    QList<QString> m_filterReadStatuses{};
};

#endif // BOOKSFILTER_H
