#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T13:58:38
#
#-------------------------------------------------

QT       -= gui
QT       += widgets printsupport

TARGET = gSimModel
TEMPLATE = lib

DEFINES += GSIMMODEL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    simModel/src/simModel.cpp \
    simModel/src/baseSimModel.cpp \
    simModel/src/simModelElement.cpp

HEADERS += \
    simModel/inc/simModel.h \
    simModel/inc/gsimmodel_global.h \
    simModel/inc/baseSimModel.h \
    simModel/inc/simModelElement.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-simModules/release/ -lsimModules
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-simModules/debug/ -lsimModules
else:unix: LIBS += -L$$PWD/../build-simModules/ -lsimModules

INCLUDEPATH += simModules/inc
INCLUDEPATH += simModel/inc/
INCLUDEPATH += $$PWD/simModules
DEPENDPATH += $$PWD/simModules
