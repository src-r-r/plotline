TEMPLATE = subdirs

SUBDIRS += CuteMarkEd/3rdparty/

SOURCES += CuteMarkEd/app/markdowneditor.cpp \
    CuteMarkEd/app/markdownhighlighter.cpp \
    CuteMarkEd/app/highlightworkerthread.cpp

HEADERS += CuteMarkEd/app/markdowneditor.h \
    CuteMarkEd/app/markdownhighlighter.h \
    CuteMarkEd/app/highlightworkerthread.h

INCLUDEPATH += CuteMarkEd/3rdparty/hunspell/src/

# build order: 3rdparty -> libs -> app-static -> app & test
libs.depends = 3rdparty
app.depends = libs app-static
