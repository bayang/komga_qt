#include "seriesfiltersortproxymodel.h"
#include "seriesmodel.h"
#include "mastercontroller.h"

SeriesFilterSortProxyModel::SeriesFilterSortProxyModel(QObject *parent) :
    QSortFilterProxyModel{parent}
{

}
bool SeriesFilterSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    qDebug() << "filter row " << source_parent.parent().row() << " so " << source_row;
    if (libraryId() == MasterController::DEFAULT_LIBRARY_ID) {
        return true;
    }
    int dat = parentModel()->get(source_row)->libraryId();

//    qDebug() << "dat " << dat << " lib " << libraryId();
    return dat == libraryId();
}

SeriesModel *SeriesFilterSortProxyModel::parentModel() const
{
    return m_parentModel;
}

void SeriesFilterSortProxyModel::setParentModel(SeriesModel *parentModel)
{
    m_parentModel = parentModel;
}

int SeriesFilterSortProxyModel::libraryId() const
{
    return m_libraryId;
}

void SeriesFilterSortProxyModel::setLibraryId(int libraryId)
{
    qDebug() << "lib id " << libraryId << " row " << rowCount(index(0, 0));
    m_libraryId = libraryId;
    emit invalidateFilter();
}
