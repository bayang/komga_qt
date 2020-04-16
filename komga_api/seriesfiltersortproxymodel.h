#ifndef SERIESFILTERSORTPROXYMODEL_H
#define SERIESFILTERSORTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>
#include "seriesmodel.h"

class SeriesFilterSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SeriesFilterSortProxyModel(QObject *parent = nullptr);

    // QSortFilterProxyModel interface
    int libraryId() const;
    void setLibraryId(int libraryId);

    SeriesModel *parentModel() const;
    void setParentModel(SeriesModel *parentModel);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    int m_libraryId{-100};
    SeriesModel *m_parentModel{nullptr};
};

#endif // SERIESFILTERSORTPROXYMODEL_H
