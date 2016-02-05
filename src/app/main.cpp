#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{

    static const QString APP_DESCRIPTION = QString("Application to help plan,")
            + QString(" organize, and write a novel."),
        ARG_NOVEL = "novel",
        DESC_NOVEL = "Path to a Plotline novel project.";

    static int POS_NOVEL = 0;

    QApplication a(argc, argv);

    // Set the parser.
    QCommandLineParser parser;
    parser.setApplicationDescription(APP_DESCRIPTION);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(ARG_NOVEL, DESC_NOVEL, "[novel]");

    parser.process(a);

    // Set app information for settings.
    QCoreApplication::setOrganizationName("Renegade Engineer");
    QCoreApplication::setOrganizationDomain("rngr.me");
    QCoreApplication::setApplicationName("Plotline");

    // Get the positional arguments

    QStringList posArgs = parser.positionalArguments();
    QString novelPath;
    if (posArgs.length() >= POS_NOVEL)
        novelPath = posArgs[POS_NOVEL];

    MainWindow w;
    w.show();

    if (!novelPath.isNull())
        w.openNovel(novelPath);

    return a.exec();
}
