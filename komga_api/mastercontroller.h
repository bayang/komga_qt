#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "komga_api_global.h"
#include "library.h"
#include "series.h"

class KOMGA_API_EXPORT MasterController : public QObject
{
    Q_OBJECT
public:
    explicit MasterController(QObject *parent = nullptr);

signals:
    void goSeriesView();
    void goBooksView();

public slots:
    void setSelectedLibrary(Library* selectedLibrary);

};

#endif // MASTERCONTROLLER_H
