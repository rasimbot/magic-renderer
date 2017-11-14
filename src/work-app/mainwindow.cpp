#include "stdafx.h"
#include "mainwindow.h"
#include "drawarea.h"
#include "ui_mainwindow.h"
#include <QtGui/QPainter>
#include <QGridLayout>
#include <QtGui/QPainter>
#include <QFileDialog>
#include <ball.h>
#include <triangle.h>
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
    m_r.setCameraSizes(2, 2, 2);

    m_r.look(Magic::Vector3(0, 0, 0), Magic::Vector3(0, 0, 10), Magic::Vector3(0, 1, 0));

    auto l_object1(std::make_unique<Magic::Ball>(Magic::Vector3(0, -1, 6), 0.8, false, Magic::RGBf{ 0.6f, 0.6f, 0.6f }));
    m_r.add(l_object1.get());
    l_object1.release();

    auto l_object2(std::make_unique<Magic::Ball>(Magic::Vector3(0, 1, 6), 0.8, true, Magic::RGBf{ 0.95f, 0.95f, 0.05f }));
    m_r.add(l_object2.get());
    l_object2.release();

    auto l_object3(std::make_unique<Magic::Triangle>(Magic::Vector3(-2, -2, 4),
                                                     Magic::Vector3(-2, 2, 8),
                                                     Magic::Vector3(-2, 2, 4),
                                                     true, Magic::RGBf{ 0.05f, 0.95f, 0.95f }));
    m_r.add(l_object3.get());
    l_object3.release();

    auto l_object4(std::make_unique<Magic::Triangle>(Magic::Vector3(-2, -2, 4),
                                                     Magic::Vector3(-2, -2, 8),
                                                     Magic::Vector3(-2, 2, 8),
                                                     true, Magic::RGBf{ 0.05f, 0.95f, 0.95f }));
    m_r.add(l_object4.get());
    l_object4.release();

    auto l_object5(std::make_unique<Magic::Triangle>(Magic::Vector3(2, 2, 4),
                                                     Magic::Vector3(2, 2, 8),
                                                     Magic::Vector3(2, -2, 4),
                                                     false, Magic::RGBf{ 0.5f, 0.05f, 0.5f }));
    m_r.add(l_object5.get());
    l_object5.release();

    auto l_object6(std::make_unique<Magic::Triangle>(Magic::Vector3(2, -2, 8),
                                                     Magic::Vector3(2, -2, 4),
                                                     Magic::Vector3(2, 2, 8),
                                                     false, Magic::RGBf{ 0.5f, 0.05f, 0.5f }));
    m_r.add(l_object6.get());
    l_object6.release();

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
