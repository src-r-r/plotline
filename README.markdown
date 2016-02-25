# Plotline

Plotline is an application to assist in the creation of a novel. While this does
not fully replace the old-school P&P (pencil & paper) method, it is nice to have
everything in one place. Some of the [planned] features include:

- Planning the novel plot arc, form inciting incident to the climax.
- Adding characters, with prompts for character biographies.
- Creating plotlines for the novel, and assigning characters as part of the
  plotlines.
- Adding scenes to the novel to plan out exactly how the novel will work out.
- Best feature: a full-fleged editor, with markdown syntax highlighting support
  and a distraction-free mode.
- Better feature: binding the novel content into a various format, ebook or
  otherwise.

## Current State

The back-end works fine and passes all tests. If someone wants to go for more
test coverage I wouldn't complain.

After a revamp to refactor the code into the seperate tab frames I've been
reconnecting the signals. The basic theory looks like this:

                        [Main App, *novel]
                            |
         +---------+--------+-----------+-----------+
         |         |        |           |           |
        Novel    Character  Plotline   Scene     Chapter
        Frame    Frame      Frame      frame     frame
        [*novel]  [*novel]   [*novel]   [*novel]  [*novel]

Each frame will contain a pointer to the currently-opened novel stored in the
pointer `novel`. Each frame corresponds to the named backend class, so
`NovelFrame` is the view for the `Novel` class, `CharacterFrame` is the view for
the `Character` class and so-on.

Each frame is a subclass `PlotlineAppFrame`, which inherits the signal
`novelModified()` (which will notify the `MainWindow` when a change occurs)
and the slots `noNovelLoad()` (which will update the frame fields when a new
novel is loaded) and `onNovelNew()` (which will clear the frame's fields).

## Getting a Development Environment Set Up

### Getting Qt

Plotline was developed in Qt, a C++ applicaiton framework. If you're new to Qt,
now is the best time to learn!

Side note: if you're new to Qt, Qt doesn't use a conventional build system like
CMake or Make. Instead, it uses QMake, which generates the Make files and meta
objects. So if you try to load the project in KDevelop or Eclipse or try to
compile on the command line it might get kind of frustrating. QtCreator was used
to develop this application, and that's what I would recommend.

Okay, back to set-up.

First thing's first, you'll need to install Qt5. Either install it with your
distribution's package manager (in the case of Linux) or download from
[Qt.io](http://www.qt.io/) and install that way.

### Getting the source.

Installing Qt should have also installed QtCreator. Open QtCreator and go to
**File > New File or Project > Import Project > Git Clone**. In *Repository*
enter `https://github.com/freckles-the-pirate/plotline.git`. Check
**Recursive** --this will import submodules. If the current version doesn't
have submodules, most likely others will.

#### Command line

Alternatively, if you're a command-line mastro, you can git clone the
repository:

    $ git clone https://github.com/freckles-the-pirate/plotline.git
    $ cd plotline
    $ git submodule init
    $ git submdoule sync

And then open the project with **File > Open File or Project**, and open the
Project (`.pro`) file.


### Important!!! Set the Library path

One more thing needs to be attended to. The core application code (in **lib** )
is a static library in order to allow linking with either the **test**
subproject or the **app** subproject.

To add this path to the library, go to the **Projects** tab along the lefthand
side of QtDesigner. Up at the top click on the **Run** tab. Expand the
**Environment** section and modify the `LD_LIBRARY_PATH` variable to append the
path `../lib/`. For example, if the original value was

    /usr/lib/x86_64-linux-gnu/

Modify the value to look like this:

    /usr/lib/x86_64-linux-gnu/:../lib/

Remember, `:` means "append" in BASH. ;-)

Do the same for the other subprojects by selecting the run button (that looks
like this: ![Qt Run Button](./doc/images/qt-run-button.png) )
