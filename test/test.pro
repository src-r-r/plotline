#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T08:51:39
#
#-------------------------------------------------

QT       += testlib core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tst_novel
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_novel.cpp \
    tst_chapter.cpp

# Sources from main program

INCLUDEPATH += ../src/
HEADERS += ../src/chapter.h \
           ../src/character.h \
           ../src/completable.h \
           ../src/mainwindow.h \
           ../src/novel.h \
           ../src/plotline.h \
           ../src/scene.h \
           ../src/sceneitemmodel.h
SOURCES += ../src/chapter.cpp \
           ../src/character.cpp \
           ../src/completable.cpp \
           ../src/main.cpp \
           ../src/mainwindow.cpp \
           ../src/novel.cpp \
           ../src/plotline.cpp \
           ../src/scene.cpp \
           ../src/sceneitemmodel.cpp

HEADERS -= ../src/mainwindow.h

SOURCES -= ../src/main.cpp \
    ../src/mainwindow.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"
