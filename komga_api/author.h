#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include "komga_api_global.h"

class KOMGA_API_EXPORT author: public QObject
{
    Q_OBJECT
public:
    author(QObject *parent = nullptr);
};

#endif // AUTHOR_H
