 
TEMPLATE = app

TARGET = Plotline

QT       += core gui webkitwidgets printsupport

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
    ../lib

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
    revisiondialog.h \
    markuphighlighter.h \
    styleproxy.h \
    styleproxyparser.h \
    scenelistdialog.h \
    fullscreeneditor.h \
    chapterfilter.h \
    chapterreorderdialog.h \
    publisherdialog.h \
    scenefilter.h \
    savethread.h

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
    revisiondialog.cpp \
    markuphighlighter.cpp \
    styleproxy.cpp \
    styleproxyparser.cpp \
    scenelistdialog.cpp \
    fullscreeneditor.cpp \
    chapterfilter.cpp \
    chapterreorderdialog.cpp \
    publisherdialog.cpp \
    scenefilter.cpp \
    savethread.cpp

##
# Depending on whether we're building the libraries statically or dynamically,
# Either the .so will be found or the .a will be found.
# There is probably a more elegant solution.
##

exists($$OUT_PWD/../lib/libplotline.a){
    LIBS += $$OUT_PWD/../lib/libplotline.a
    PRE_TARGETDEPS += $$OUT_PWD/../lib/libplotline.a
}

exists($$OUT_PWD/../lib/libplotline.so){
    LIBS += $$OUT_PWD/../lib/libplotline.so
    PRE_TARGETDEPS += $$OUT_PWD/../lib/libplotline.so
}

FORMS += mainwindow.ui \
    preferencesdialog.ui \
    plotlinedialog.ui \
    characterframe.ui \
    plotframe.ui \
    sceneframe.ui \
    chaptersframe.ui \
    novelframe.ui \
    revisiondialog.ui \
    scenelistdialog.ui \
    fullscreeneditor.ui \
    chapterreorderdialog.ui \
    publisherdialog.ui

RESOURCES += ../res/plotline.qrc

styles.path = $$DESTDIR/styles
styles.files = $$PWD/styles/*.json

INSTALLS += styles

CONFIG += c++11

REQUIRES += $$PWD/../lib
#LIBS += $$PWD/../lib
