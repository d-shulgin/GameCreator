#include "main_window.h"
#include <QApplication>

#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    //w.showFullScreen();

    return a.exec();
}
