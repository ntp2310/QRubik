#include "mainwindow.h"
#include <QApplication>
#include <GL/freeglut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    MainWindow w;
    w.show();
    return app.exec();
}
