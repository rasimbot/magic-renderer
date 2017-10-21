#ifndef __WORK_APP_MAINWINDOW_H
#define __WORK_APP_MAINWINDOW_H

#include <QWidget>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *a_parent = nullptr);
    virtual ~MainWindow();

private:
    Ui::MainWindow *m_ui;
};

#endif // __WORK_APP_MAINWINDOW_H
