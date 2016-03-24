#include "mainwindow.h"
#include <QApplication>

QString cmd_path;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cmd_path = QCoreApplication::applicationDirPath();    
    MainWindow w;
    w.show();

    return a.exec();
}
