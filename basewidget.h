#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

//widget  实现界面鼠标移动效果
class BaseWidget: public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    QPoint posMouseOrigin; //鼠标原始位置
};


#endif // BASEWIDGET_H
