 
TEMPLATE = app

TARGET = plotline-UnitTest

QT += testlib

HEADERS += tst_chapter.h \
    tst_character.h \
    tst_novel.h \
    tst_plotline.h \
    tst_scene.h

SOURCES += main.cpp \
    tst_chapter.cpp \
    tst_character.cpp \
    tst_novel.cpp \
    tst_plotline.cpp \
    tst_scene.cpp

INCLUDEPATH += \
    ../../src/lib

LIBS += ../../src/lib/libplotline.so

CONFIG += console testcase c++11
