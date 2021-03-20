#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <iostream>
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include <fstream>
#include <sstream>
#include<math.h>
#include <QImage>
#include "face.hpp"

using namespace std;
using namespace cv;

class CameraThread : public QThread
{
    Q_OBJECT
public:
    CameraThread();
    int Predict(Mat src_image);
    void run();//任务处理线程
    void FaceRecognition();

signals:
    void sigFaceResult(QImage image);
    void sigIDResult(QString id);

public:
   bool isWork;

private:
    RNG g_rng;
    Ptr<face::FaceRecognizer> model;
    VideoCapture cap;
    CascadeClassifier cascade;//分类器--人脸检测所用
    Mat frame;//摄像头读入一帧图像
    Mat gray;//灰度处理后图像
};

#endif // CAMERATHREAD_H
