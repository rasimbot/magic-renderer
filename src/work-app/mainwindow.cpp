#include "stdafx.h"
#include "mainwindow.h"
#include "drawarea.h"
#include "ui_mainwindow.h"
#include <QtGui/QPainter>
#include <QGridLayout>
#include <QtGui/QPainter>
#include <QFileDialog>
#include <ball.h>
#include <memory>

MainWindow::MainWindow(QWidget *a_parent) :
    QWidget(a_parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_drawArea = new DrawArea(m_ui->widget_drawAreaContainer);
    auto l_layout = new QGridLayout(m_ui->widget_drawAreaContainer);
    l_layout->addWidget(m_drawArea);
    l_layout->setMargin(0);
    connect(m_drawArea, SIGNAL(onPaint()), SLOT(onDrawAreaPaint()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onDrawAreaPaint()
{
    const auto l_drawArea = static_cast<QWidget *>(sender());
    QPainter l_painter(l_drawArea);
    l_painter.setBrush(QBrush(QColor(0, 0, 0, 255)));
    l_painter.drawRect(l_drawArea->rect());
    l_painter.drawImage(0, 0, m_i);
}

void MainWindow::on_pushButton_do_clicked()
{
    Q_ASSERT(m_ui != nullptr && m_drawArea != nullptr);
    m_r.setBufferSize(m_drawArea->width(), m_drawArea->height());
    m_r.setCameraSizes(1, 1, 2);

    m_r.look(Magic::Vector3{ 0, 0, 0 }, Magic::Vector3{ 0, 0, 10 }, Magic::Vector3{ 0, 1, 0 });

    auto l_object1(std::make_unique<Magic::Ball>(Magic::Vector3{ 0.2f, 0, 8 }, 1, Magic::ARGB{ 0, 0, 255 }));
    auto l_object2(std::make_unique<Magic::Ball>(Magic::Vector3{ -0.1f, 0, 4 }, 0.4, Magic::ARGB{ 0, 255, 0 }));
    m_r.add(l_object1.get());
    l_object1.release();
    m_r.add(l_object2.get());
    l_object2.release();

    m_r.doIt();

    m_i = QImage(reinterpret_cast<const uchar *>(m_r.buf()),
                    int(m_r.bufWidth()), int(m_r.bufHeight()), QImage::Format_ARGB32);

    update();
}

void MainWindow::on_pushButton_save_clicked()
{
    const auto l_filepath(QFileDialog::getSaveFileName(this,
                            windowTitle() + " - Save", "image1.png", "Images (*.png)"));
    if (l_filepath.isEmpty()) return;
    m_i.save(l_filepath, "PNG");
}
