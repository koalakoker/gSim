#ifndef GSIMMODEL_GLOBAL_H
#define GSIMMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GSIMMODEL_LIBRARY)
#  define GSIMMODELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GSIMMODELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GSIMMODEL_GLOBAL_H
