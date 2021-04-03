#include "basemainwindow.h"

BaseMainWindow::BaseMainWindow(QWidget *parent):
    QMainWindow(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
//    this->setWindowOpacity(0.9);//设置透明
}

void BaseMainWindow::mousePressEvent(QMouseEvent *ev)
{
    this->posMouseOrigin = QCursor::pos(); //cursor是一个光标类
}

void BaseMainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint ptMouseNow = QCursor::pos();
    QPoint ptDelta = ptMouseNow - this->posMouseOrigin;
    move(this->pos() + ptDelta);
    posMouseOrigin = ptMouseNow;
}

void BaseMainWindow::mouseReleaseEvent(QMouseEvent *ev)
{

}
