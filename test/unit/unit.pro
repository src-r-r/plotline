 
TEMPLATE = app

TARGET = plotline-UnitTest

QT += core gui webkitwidgets printsupport testlib

HEADERS += tst_chapter.h \
    tst_character.h \
    tst_novel.h \
    tst_plotline.h \
    tst_scene.h \
    tst_revision.h \
    testcharacterparser.h \
    tst_utils.h

SOURCES += main.cpp \
    tst_chapter.cpp \
    tst_character.cpp \
    tst_novel.cpp \
    tst_plotline.cpp \
    tst_scene.cpp \
    tst_revision.cpp \
    testcharacterparser.cpp \
    tst_utils.cpp

DISTFILES += \
    fixtures/character-deserialize.json \
    fixtures/chapter-deserialize.json \
    fixtures/novel-deserialize.json \
    fixtures/revision-deserialize.json \
    fixtures/revision-bug-test.json

INCLUDEPATH += \
    ../../src/lib \
    ../../src/app

LIBS += $$OUT_PWD/../../src/lib/libplotline.so

CONFIG += console testcase c++11
