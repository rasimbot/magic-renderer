#ifndef __WORK_APP_DRAWAREA_H
#define __WORK_APP_DRAWAREA_H

#include <QWidget>

class DrawArea : public QWidget
{
    Q_OBJECT

public:
    explicit DrawArea(QWidget *a_parent = nullptr);
    virtual ~DrawArea();

signals:
    void onPaint();

private:
    void paintEvent(QPaintEvent *a);
};

#endif // __WORK_APP_DRAWAREA_H
