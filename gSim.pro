#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T07:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gSim
TEMPLATE = app


SOURCES +=  main.cpp\
            gsim.cpp \
            simTemplates/simView/baseSimView.cpp \
            simTemplates/simView/commonSimView.cpp \

HEADERS  += gsim.h \
            simTemplates/simView/baseSimView.h \
            simTemplates/simView/commonSimView.h \

FORMS    += gsim.ui \
            simTemplates/simView/baseSimView.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-gSimModel/release/ -lgSimModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-gSimModel/debug/ -lgSimModel
else:unix: LIBS += -L$$PWD/../build-gSimModel/ -lgSimModel

INCLUDEPATH += $$PWD/simModel
DEPENDPATH += $$PWD/simModel

