#include "stdafx.h"
#include "mainwindow.h"
#include <QApplication>
#include <renderer.h>
#include <vector4.h>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector4D>
#include <sstream>

int main(int a_argc, char *a_argv[])
{
    QApplication a(a_argc, a_argv);
    MainWindow w;
    w.show();

    Magic::Renderer l_renderer;
    const auto q1(l_renderer.look(Magic::Vector3(0, 0, 0), Magic::Vector3(-9.4f, 0, 3.4f), Magic::Vector3(0, 1, 0)));
    const auto q2(l_renderer.look(Magic::Vector3(0, 0, 5), Magic::Vector3(0, 0, 10), Magic::Vector3(0, 1, 0)));

    const auto z(q2 * q1 * Magic::Vector3(-5, 0, 5));

    return a.exec();
}
