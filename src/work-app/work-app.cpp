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
    const auto q1(l_renderer.look(Magic::Vector3{ -1, 2, -3 }, Magic::Vector3{ -1, 2, 3 }, Magic::Vector3{ 0, 5, 0 }));
    const auto q2(l_renderer.look(Magic::Vector3{ -4, 5, -6 }, Magic::Vector3{ -4, 5, 6 }, Magic::Vector3{ 0, 5, 0 }));

    const auto r(Magic::Vector3{ 10, 10, 10 });
    const auto u(q1 * q2 * r);

    l_renderer.setBufferSize(100, 100);
    l_renderer.doIt();

    Magic::Vector4 v4{ r, 1 };

    return a.exec();
}
