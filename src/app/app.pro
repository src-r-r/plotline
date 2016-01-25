 
TEMPLATE = app

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/../lib \
    $$PWD/../3rdparty/

TARGET = plotline

HEADERS +=  mainwindow.h \
    characteritemmodel.h \
    sceneitemmodel.h

SOURCES += main.cpp \
    mainwindow.cpp \
    characteritemmodel.cpp \
    sceneitemmodel.cpp

FORMS += mainwindow.ui
