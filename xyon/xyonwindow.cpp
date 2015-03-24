#include "xyonwindow.h"
#include <QDebug>

XyonWindow::XyonWindow()
{
}

void XyonWindow::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "MousePress";
    this->clickPos = e->pos();
}

void XyonWindow::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << "MouseMove";
    this->setPosition(e->globalPos() - clickPos);
}
