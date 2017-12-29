#ifndef OCEAIR_GLOBAL_H
#define OCEAIR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OCEAIR_LIBRARY)
#  define OCEAIRSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OCEAIRSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OCEAIR_GLOBAL_H
