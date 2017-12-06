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

    return a.exec();
}
