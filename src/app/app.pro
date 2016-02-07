 
TEMPLATE = app

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
    ../lib

TARGET = plotline

HEADERS +=  mainwindow.h \
    characteritemmodel.h \
    sceneitemmodel.h \
    preferencesdialog.h \
    plotlineitemmodel.h \
    plotlineitemdelegate.h \
    plotlinedialog.h \
    characterframe.h \
    plotframe.h \
    sceneframe.h \
    chaptersframe.h \
    novelframe.h \
    plotlineappframe.h \
    modelcheckbox.h \
    characterhighlighter.h \
    chaptermodel.h \
    revisiondialog.h

SOURCES += main.cpp \
    mainwindow.cpp \
    characteritemmodel.cpp \
    sceneitemmodel.cpp \
    preferencesdialog.cpp \
    plotlineitemmodel.cpp \
    plotlineitemdelegate.cpp \
    plotlinedialog.cpp \
    characterframe.cpp \
    plotframe.cpp \
    sceneframe.cpp \
    chaptersframe.cpp \
    novelframe.cpp \
    plotlineappframe.cpp \
    modelcheckbox.cpp \
    characterhighlighter.cpp \
    chaptermodel.cpp \
    revisiondialog.cpp

LIBS += \
    ../lib/libplotline.so

PRE_TARGETDEPS += ../lib/libplotline.so

FORMS += mainwindow.ui \
    preferencesdialog.ui \
    plotlinedialog.ui \
    characterframe.ui \
    plotframe.ui \
    sceneframe.ui \
    chaptersframe.ui \
    novelframe.ui \
    revisiondialog.ui

RESOURCES += ../res/plotline.qrc

CONFIG += c++11
