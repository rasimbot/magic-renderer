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
#include <material1.h>
#include <material2.h>
#include <checkermaterial.h>
#include <shinymaterial.h>
#include <array>

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

    auto l_material1(std::make_unique<Magic::Material1>(&m_r, Magic::RGBf{ 0.8f, 0.98f, 0.98f }));
    m_r.add(l_material1.get());
    auto l_rpMaterial1 = l_material1.release();

    auto l_material2(std::make_unique<Magic::ShinyMaterial>(&m_r, Magic::RGBf{ 0.95f, 0.95f, 0.95f }));
    m_r.add(l_material2.get());
    auto l_rpMaterial2 = l_material2.release();

    auto l_object1(std::make_unique<Magic::Ball1>(&m_r, Magic::Vector3(-1, 0, 6), 0.8, l_rpMaterial1));
    m_r.add(l_object1.get());
    m_ball1 = l_object1.release();

    auto l_object2(std::make_unique<Magic::Ball1>(&m_r, Magic::Vector3(1, 0, 6), 0.8, l_rpMaterial2));
    m_r.add(l_object2.get());
    m_ball2 = l_object2.release();

    auto l_material3(std::make_unique<Magic::Material2>(&m_r, Magic::RGBf{ 0.25f, 0.6f, 0.6f }));
    m_r.add(l_material3.get());
    auto l_rpMaterial3 = l_material3.release();

    const Magic::V3Triple l_inWorld3{ Magic::Vector3(-2, -2, 4), Magic::Vector3(-2, -2, 8), Magic::Vector3(-2, 2, 8) };
    auto l_object3(std::make_unique<Magic::Triangle>(&m_r, l_inWorld3, l_rpMaterial3, Magic::V2Triple()));
    m_r.add(l_object3.get());
    l_object3.release();

    const Magic::V3Triple l_inWorld4{ Magic::Vector3(-2, -2, 4), Magic::Vector3(-2, 2, 8), Magic::Vector3(-2, 2, 4) };
    auto l_object4(std::make_unique<Magic::Triangle>(&m_r, l_inWorld4, l_rpMaterial3, Magic::V2Triple()));
    m_r.add(l_object4.get());
    l_object4.release();

    const Magic::V3Triple l_inWorld5{ Magic::Vector3(2, -2, 4), Magic::Vector3(2, 2, 4), Magic::Vector3(2, 2, 8) };
    auto l_object5(std::make_unique<Magic::Triangle>(&m_r, l_inWorld5, l_rpMaterial3, Magic::V2Triple()));
    m_r.add(l_object5.get());
    l_object5.release();

    const Magic::V3Triple l_inWorld6{ Magic::Vector3(2, -2, 4), Magic::Vector3(2, 2, 8), Magic::Vector3(2, -2, 8) };
    auto l_object6(std::make_unique<Magic::Triangle>(&m_r, l_inWorld6, l_rpMaterial3, Magic::V2Triple()));
    m_r.add(l_object6.get());
    l_object6.release();

    auto l_material4(std::make_unique<Magic::Material1>(&m_r, Magic::RGBf{ 0.98f, 0.98f, 0.8f }));
    m_r.add(l_material4.get());
    auto l_rpMaterial4 = l_material4.release();

    const Magic::V3Triple l_inWorld7{ Magic::Vector3(2, 2, 4), Magic::Vector3(-2, 2, 4), Magic::Vector3(-2, 2, 8) };
    auto l_object7(std::make_unique<Magic::Triangle>(&m_r, l_inWorld7, l_rpMaterial4, Magic::V2Triple()));
    m_r.add(l_object7.get());
    l_object7.release();

    const Magic::V3Triple l_inWorld8{ Magic::Vector3(2, 2, 4), Magic::Vector3(-2, 2, 8), Magic::Vector3(2, 2, 8) };
    auto l_object8(std::make_unique<Magic::Triangle>(&m_r, l_inWorld8, l_rpMaterial4, Magic::V2Triple()));
    m_r.add(l_object8.get());
    l_object8.release();

    auto l_material5(std::make_unique<Magic::CheckerMaterial>(&m_r, Magic::RGBf{ 0.1f, 0.1f, 0.6f },
                                                                    Magic::RGBf{ 0.6f, 0.1f, 0.1f }));
    m_r.add(l_material5.get());
    auto l_rpMaterial5 = l_material5.release();

    const Magic::V3Triple l_inWorld9{ Magic::Vector3(-2, -2, 4), Magic::Vector3(2, -2, 4), Magic::Vector3(2, -2, 8) };
    const Magic::V2Triple l_inMaterial9{ Magic::Vector2{ 0, 0 }, Magic::Vector2{ 10, 0 }, Magic::Vector2{ 10, 10 } };
    auto l_object9(std::make_unique<Magic::Triangle>(&m_r, l_inWorld9, l_rpMaterial5, l_inMaterial9));
    m_r.add(l_object9.get());
    l_object9.release();

    const Magic::V3Triple l_inWorld10{ Magic::Vector3(-2, -2, 4), Magic::Vector3(2, -2, 8), Magic::Vector3(-2, -2, 8) };
    const Magic::V2Triple l_inMaterial10{ Magic::Vector2{ 0, 0 }, Magic::Vector2{ 10, 10 }, Magic::Vector2{ 0, 10 } };
    auto l_object10(std::make_unique<Magic::Triangle>(&m_r, l_inWorld10, l_rpMaterial5, l_inMaterial10));
    m_r.add(l_object10.get());
    l_object10.release();

    std::vector<size_t> l_strategy{ /*48, 24, */12, 6, 3 };
    m_r.setRaysNumStrategy(l_strategy);
    m_r.doIt();

    m_i = QImage(reinterpret_cast<const uchar *>(m_r.buf()),
                    int(m_r.bufWidth()), int(m_r.bufHeight()), QImage::Format_ARGB32);

    repaint();

    const QString l_template("hit: %1\nmisses: %2\ndropped: %3\n");
    const QString l_stat(l_template.arg(m_r.hit()).arg(m_r.misses()).arg(m_r.dropped()));
    m_ui->plainTextEdit_log->setPlainText(l_stat);
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
