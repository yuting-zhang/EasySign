#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T19:04:31
#
#-------------------------------------------------

QT       += core gui  multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasySign
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videoplayer.cpp \
    dictionary.cpp \
    configdata.cpp \
    studyqueue.cpp \
    chooseunits.cpp

HEADERS  += mainwindow.h \
    videoplayer.h \
    dictionary.h \
    configdata.h \
    studyqueue.h \
    chooseunits.h

FORMS    += mainwindow.ui \
    videoplayer.ui \
    chooseunits.ui

CONFIG += C++11

RESOURCES += \
    resource.qrc

RC_FILE = resource.rc
