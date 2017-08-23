#ifndef SIMMODULES_GLOBAL_H
#define SIMMODULES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIMMODULES_LIBRARY)
#  define SIMMODULESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIMMODULESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIMMODULES_GLOBAL_H
