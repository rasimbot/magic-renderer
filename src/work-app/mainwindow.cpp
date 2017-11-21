#include "stdafx.h"
#include "mainwindow.h"
#include "drawarea.h"
#include "ui_mainwindow.h"
#include <QtGui/QPainter>
#include <QGridLayout>
#include <QtGui/QPainter>
#include <QFileDialog>
#include <memory>
#include <QtGui/QMatrix4x4>

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

    auto l_object1(std::make_unique<Magic::Ball>(Magic::Vector3(-1, 0, 6), 0.9, false, Magic::RGBf{ 0.95f, 0.95f, 0.95f }));
    m_r.add(l_object1.get());
    m_ball1 = l_object1.release();

    auto l_object2(std::make_unique<Magic::Ball>(Magic::Vector3(1, 0, 6), 0.9, true, Magic::RGBf{ 0.95f, 0.95f, 0.05f }));
    m_r.add(l_object2.get());
    m_ball2 = l_object2.release();

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
                                                     false, Magic::RGBf{ 0.95f, 0.05f, 0.95f }));
    m_r.add(l_object5.get());
    l_object5.release();

    auto l_object6(std::make_unique<Magic::Triangle>(Magic::Vector3(2, -2, 8),
                                                     Magic::Vector3(2, -2, 4),
                                                     Magic::Vector3(2, 2, 8),
                                                     false, Magic::RGBf{ 0.95f, 0.05f, 0.95f }));
    m_r.add(l_object6.get());
    l_object6.release();

    m_r.setCameraRaysNum(128);
    m_r.setReflRaysNum(32);
    m_r.doIt();

    m_i = QImage(reinterpret_cast<const uchar *>(m_r.buf()),
                    int(m_r.bufWidth()), int(m_r.bufHeight()), QImage::Format_ARGB32);

    repaint();
}

void MainWindow::on_pushButton_save_clicked()
{
    const auto l_filepath(QFileDialog::getSaveFileName(this,
                            windowTitle() + " - Save", "image1.png", "Images (*.png)"));
    if (l_filepath.isEmpty()) return;
    m_i.save(l_filepath, "PNG");
}

void MainWindow::on_pushButton_saveSlides_clicked()
{
    if (m_ball1 == nullptr || m_ball2 == nullptr) return;

    const auto l_dir(QFileDialog::getExistingDirectory(this, windowTitle() + " - Save directory"));
    if (l_dir.isEmpty()) return;

    double l_a1 = 0, l_a2 = 0;
    for (int i = 0; i < 3000; i++)
    {
        QMatrix4x4 l_m;
        l_m.translate(QVector3D(0, 0, 6));
        l_m.rotate(l_a1, QVector3D(0, 1, 0));
        l_m.rotate(l_a2, QVector3D(0, 0, 1));
        const QVector3D l_v1(l_m * QVector3D(-1, 0, 0)), l_v2(l_m * QVector3D(1, 0, 0));
        m_ball1->set(Magic::Vector3(l_v1.x(), l_v1.y(), l_v1.z()));
        m_ball2->set(Magic::Vector3(l_v2.x(), l_v2.y(), l_v2.z()));

        m_r.doIt();

        m_i = QImage(reinterpret_cast<const uchar *>(m_r.buf()),
                        int(m_r.bufWidth()), int(m_r.bufHeight()), QImage::Format_ARGB32);

        repaint();

        m_i.save(QString("%1/%2.png").arg(l_dir).arg(i), "PNG");

        l_a1 += 0.04;
        l_a2 += 0.28;
    }
}
