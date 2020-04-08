#ifndef KOMGA_API_GLOBAL_H
#define KOMGA_API_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KOMGA_API_LIBRARY)
#  define KOMGA_API_EXPORT Q_DECL_EXPORT
#else
#  define KOMGA_API_EXPORT Q_DECL_IMPORT
#endif

#endif // KOMGA_API_GLOBAL_H
