# Plotline

## Setting Up for Development

Plotline is written in Qt, and, therefore, it's really easy to set up in
QtCreator. If you're new to QtCreator, now's the perfect time to get yourself
acquainted! Head over to [qt.io](https://qt.io) to get set up with Qt and
QtCreator.

Once you're set up, clone the repository...

    $ git clone {{ plotline-repository }}

...and initialize the submodules:

    $ git submodule init

Three other submodules will be cloned:

 - CuteMarkEd: heavily used for the Markdown editor.
 - discount: library used to Markdown parsing (dependency of CuteMarkEd)
 - hunspell: spell-checker library.

## IMPORTANT!! BUILD EACH SUBMODULE!!

I'll be working on automatically building each submodule by using QMake. Until
then each submodule should be built before building Plotline.

    $ cd src/3rdparty/discount/
    $ ./configure && make;  # don't run install (you can, but there's no point)
    $ cd ../hunspell/
    $ ./configure && make

Since CuteMarkEd uses the QMake build system it will be handled by Plotline's
QMake.
