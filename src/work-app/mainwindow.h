#ifndef __WORK_APP_MAINWINDOW_H
#define __WORK_APP_MAINWINDOW_H

#include <QWidget>
#include <renderer.h>

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

private slots:
    void onDrawAreaPaint();
    void on_pushButton_do_clicked();

private:
    Ui::MainWindow *m_ui;
    QWidget *m_drawArea = nullptr;
    QImage m_i;
    Magic::Renderer m_r;
};

#endif // __WORK_APP_MAINWINDOW_H
