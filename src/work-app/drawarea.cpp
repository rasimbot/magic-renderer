#include "stdafx.h"
#include "drawarea.h"

DrawArea::DrawArea(QWidget *a_parent) :
    QWidget(a_parent)
{}

DrawArea::~DrawArea()
{}

void DrawArea::paintEvent(QPaintEvent *a)
{
    emit onPaint();
}
