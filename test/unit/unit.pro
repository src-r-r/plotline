 
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

REQUIRES += \
    $$PWD/../../src/lib \
    $$PWD/../../src/app

INCLUDEPATH += \
    $$OUT_PWD/../../src/lib \
    $$OUT_PWD/../../src/app

##
# Depending on whether we're building the libraries statically or dynamically,
# Either the .so will be found or the .a will be found.
# There is probably a more elegant solution.
##

exists($$OUT_PWD/../../src/lib/libplotline.a){
    LIBS += $$OUT_PWD/../../src/lib/libplotline.a
}

exists($$OUT_PWD/../../src/lib/libplotline.so){
    LIBS += $$OUT_PWD/../../src/lib/libplotline.so
}

CONFIG += console testcase c++11
