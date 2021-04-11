#ifndef BASEMAINWINDOW_H
#define BASEMAINWINDOW_H

#include <QMainWindow>

//mainwindow基类  实现界面鼠标移动效果
class BaseMainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit BaseMainWindow(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    QPoint posMouseOrigin; //鼠标原始位置
};

#endif // BASEMAINWINDOW_H
