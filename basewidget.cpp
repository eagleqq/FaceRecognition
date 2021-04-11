#include "basewidget.h"

BaseWidget::BaseWidget(QWidget *parent):
    QWidget(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
//    this->setWindowOpacity(0.9);//设置透明
}

void BaseWidget::mousePressEvent(QMouseEvent *ev)
{
    //鼠标按下
    this->posMouseOrigin = QCursor::pos(); //cursor是一个光标类
}

void BaseWidget::mouseMoveEvent(QMouseEvent *ev)
{
    //鼠标移动
    QPoint ptMouseNow = QCursor::pos();
    QPoint ptDelta = ptMouseNow - this->posMouseOrigin;
    move(this->pos() + ptDelta);
    posMouseOrigin = ptMouseNow;
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    //鼠标释放
}
