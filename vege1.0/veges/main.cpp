#include "mainwindow.h"
#include "boardw.h"
#include <QApplication>
#include "dialogw.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Dialogw Board;
   // Board.hide();
    MainWindow w;
    w.show();

    return a.exec();
}
