#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T12:24:40
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs

SUBDIRS += src \
    test

QMAKE_CXXFLAGS += \
    -std=gnu++11
