 
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

##
# Depending on whether we're building the libraries statically or dynamically,
# Either the .so will be found or the .a will be found.
# There is probably a more elegant solution.
##

CONFIG += console testcase c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/lib/release/ -lplotline
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/lib/debug/ -lplotline
else:unix: LIBS += -L$$OUT_PWD/../../src/lib/ -lplotline

INCLUDEPATH += $$PWD/../../src/lib
DEPENDPATH += $$PWD/../../src/lib
