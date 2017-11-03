#include "stdafx.h"
#include "mainwindow.h"
#include <QApplication>
#include <renderer.h>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector4D>
#include <sstream>

int main(int a_argc, char *a_argv[])
{
    QApplication a(a_argc, a_argv);
    MainWindow w;
    w.show();

    Magic::Renderer l_renderer;
    l_renderer.look(Magic::Vector3{ 0, -1, -10 }, Magic::Vector3{}, Magic::Vector3{ -10, 5, 0 });

    return a.exec();
}
