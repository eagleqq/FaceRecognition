#ifndef FACETRAINWIDGET_H
#define FACETRAINWIDGET_H

#include <QWidget>
#include <QList>
#include <QStandardItemModel>
#include <QTimer>
#include "trainthread.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class FaceTrainWidget;
}

class FaceTrainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FaceTrainWidget(QWidget *parent = nullptr);
    ~FaceTrainWidget();
    QList<QString> getAllFileFolder(QString dirPath);
    void updateTableData();
    bool DeleteFileOrFolder(const QString &strPath);
    void CreateCSV();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_find_clicked();

    void on_pushButton_cap_clicked();

    void showImage();

    void slotTrainFinished();
    void slotTrainFailed();

private:
    Ui::FaceTrainWidget *ui;
    QTimer *mCapTimer; //拍照定时器
    QImage *image;
    VideoCapture cap;
    Mat frame,myFace,frame_gray;//图像，人脸，灰度图像
    CascadeClassifier cascada;
    vector<Rect> faces;//vector容器存检测到的faces
    int pic_num;

    TrainThread *mTrainThread;
};

#endif // FACETRAINWIDGET_H
