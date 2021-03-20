#ifndef BASEMAINWINDOW_H
#define BASEMAINWINDOW_H

#include <QMainWindow>


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
