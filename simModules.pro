#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T16:38:16
#
#-------------------------------------------------

QT       -= gui

TARGET = simModules
TEMPLATE = lib

DEFINES += SIMMODULES_LIBRARY

SOURCES += simModules/simmodules.cpp

HEADERS += simModules/simmodules.h\
        simModules/simmodules_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
