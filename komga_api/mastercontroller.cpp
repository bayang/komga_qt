#include "mastercontroller.h"

MasterController::MasterController(QObject *parent) :
    QObject{parent}
{

}
void MasterController::setSelectedLibrary(Library* selectedLibrary) {
    qDebug() << "selected library in mastercontroller : " << selectedLibrary->name();
}
