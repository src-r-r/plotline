#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T12:24:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plotline
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    novel.cpp \
    novelpart.cpp \
    novelbeginning.cpp \
    novelmiddle.cpp \
    novelend.cpp \
    character.cpp \
    TraitCategories/traitcategory.cpp \
    TraitCategories/novelworthiness.cpp \
    TraitCategories/goal.cpp \
    TraitCategories/appearance.cpp \
    TraitCategories/personality.cpp \
    TraitCategories/preferences.cpp \
    TraitCategories/backstory.cpp

HEADERS  += mainwindow.h \
    novel.h \
    novelpart.h \
    novelbeginning.h \
    novelmiddle.h \
    novelend.h \
    character.h \
    TraitCategories/traitcategory.h \
    TraitCategories/novelworthiness.h \
    TraitCategories/goal.h \
    TraitCategories/appearance.h \
    TraitCategories/personality.h \
    TraitCategories/preferences.h \
    TraitCategories/backstory.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
