#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#define HALF(VALUE) (VALUE) / 2
#define SCREEN_WIDTH QApplication::desktop()->width()
#define SCREEN_HEIGHT QApplication::desktop()->height()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(HALF(SCREEN_WIDTH - w.width()), HALF(SCREEN_HEIGHT - w.height()));
    w.show();
    return a.exec();
}
