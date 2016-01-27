 
TEMPLATE = app

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
    ../lib

TARGET = plotline

HEADERS +=  mainwindow.h \
    characteritemmodel.h \
    sceneitemmodel.h \
    preferencesdialog.h

SOURCES += main.cpp \
    mainwindow.cpp \
    characteritemmodel.cpp \
    sceneitemmodel.cpp \
    preferencesdialog.cpp

LIBS += ../lib/libplotline.so
PRE_TARGETDEPS += ../lib/libplotline.so

FORMS += mainwindow.ui \
    preferencesdialog.ui
