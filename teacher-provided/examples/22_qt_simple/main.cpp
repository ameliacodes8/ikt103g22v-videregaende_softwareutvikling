#include "mainwindow.h"

#include <QApplication>

// Main function is unchanged from the new project template
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
