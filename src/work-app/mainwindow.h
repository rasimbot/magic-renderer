#ifndef __WORK_APP_MAINWINDOW_H
#define __WORK_APP_MAINWINDOW_H

#include <QWidget>
#include <renderer.h>
#include <ball.h>
#include <triangle.h>

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
    void on_pushButton_save_clicked();
    void on_pushButton_saveSlides_clicked();

private:
    Ui::MainWindow *m_ui;
    QWidget *m_drawArea = nullptr;
    QImage m_i;
    Magic::Renderer m_r;
    Magic::Ball *m_ball1 = nullptr, *m_ball2 = nullptr;
};

#endif // __WORK_APP_MAINWINDOW_H
