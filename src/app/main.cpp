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
        DESC_NOVEL = "Path to a Plotline novel project.",

            T_NOVEL="novel",
            T_CHARACTER="character",
            T_PLOTLINE="plotline",
            T_SCENE="scene",
            T_CHAPTER="chapter";

    static const QStringList TABS({T_NOVEL, T_CHARACTER, T_PLOTLINE, T_SCENE,
                                  T_CHAPTER});

    static int POS_NOVEL = 0;

    QApplication a(argc, argv);

    // Set the parser.
    QCommandLineParser parser;
    parser.setApplicationDescription(APP_DESCRIPTION);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(ARG_NOVEL, DESC_NOVEL, "[novel]");

    QCommandLineOption tab = QCommandLineOption(
        {"t", "tab"},
        "Open selected tab (novel, character, plotline, scene, chapter)",
        T_NOVEL
    );
    parser.addOption(tab);

    parser.process(a);

    // Set app information for settings.
    QCoreApplication::setOrganizationName("Renegade Engineer");
    QCoreApplication::setOrganizationDomain("rngr.me");
    QCoreApplication::setApplicationName("Plotline");

    // Get the positional arguments

    QStringList posArgs = parser.positionalArguments();
    QString novelPath;
    if (POS_NOVEL < posArgs.length())
        novelPath = posArgs[POS_NOVEL];

    QString tabName = parser.value("tab");
    if (tabName.isEmpty()) tabName = parser.value("t");
    if (tabName.isEmpty()) tabName = T_NOVEL;

    // Get the correct tab.
    if (0 > TABS.indexOf(tabName)){
        qCritical() << "Invalid tab name:" << tabName;
        return 1;
    }

    MainWindow w;
    w.show();

    if (!novelPath.isNull()){
        w.openNovel(novelPath);
    }

    w.openTab(TABS.indexOf(tabName));
    return a.exec();
}
