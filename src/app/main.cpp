#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set app information for settings.
    QCoreApplication::setOrganizationName("Renegade Engineer");
    QCoreApplication::setOrganizationDomain("rngr.me");
    QCoreApplication::setApplicationName("Plotline");

    MainWindow w;
    w.show();

    return a.exec();
}
