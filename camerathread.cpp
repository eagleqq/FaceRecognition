#include "camerathread.h"
#include <QDateTime>
#include <QDebug>
#include <QImage>
#include "constants.h"

CameraThread::CameraThread()
{
    g_rng(12345);
}

int CameraThread::Predict(Mat src_image)
{
    Mat face_test;
    int predict = 0;
    //截取的ROI人脸尺寸调整
    if (src_image.rows >= 120)
    {
        //改变图像大小，使用双线性差值
        ::resize(src_image, face_test, Size(92, 112));
    }
    //判断是否正确检测ROI
    if (!face_test.empty())
    {
        //测试图像应该是灰度图
        predict = model->predict(face_test);
    }
    cout << predict << endl;
    return predict;
}

void CameraThread::run()
{
    isWork = true;
    //装载人脸识别分类器
    cascade.load(HAARCASCADE_FRONTALFACE_ALT2.toStdString());
    model = face::FisherFaceRecognizer::create();
    model->read(MyFaceFisherModel_XML.toStdString());// opencv2用load加载训练好的模型
    cap.open(0);
    while (true) {
        msleep(10);
//        cap.open(0);
        if(!isWork){
            break;
        }
        try {
           qDebug()<<"读取摄像头";
          cap>>frame;//摄像头读取头像
        } catch (exception ex) {
            qDebug() << "摄像头读取异常";
        }
        try {
           QDateTime startTime=  QDateTime::currentDateTime();
           FaceRecognition();
           qDebug()<<"FaceRecognition time=" << startTime.msecsTo(QDateTime::currentDateTime()) /1000.0;
        } catch (exception ex) {
           qDebug() << "识别异常";
           QImage tempImage = QImage((const unsigned char*)(frame.data),
                                 frame.cols, frame.rows, frame.step,
                                 QImage::Format_RGB888);
           emit sigFaceResult(tempImage);
        }
    }
    cap.release();
}

void CameraThread::FaceRecognition()
{
    vector<Rect> faces(0);//建立用于存放人脸的向量容器
    cvtColor(frame, gray, CV_RGB2GRAY);//测试图像必须为灰度图
    cascade.detectMultiScale(gray, faces, 1.1, 4,
                             CV_HAAR_DO_ROUGH_SEARCH,
                             Size(30, 30),
                             Size(500, 500));
    Mat* pImage_roi = new Mat[faces.size()];    //数组存所有的脸
    Mat face;
    Point text_lb;//文本写在的位置
    //框出人脸
    string str="NONE";
    QString result="";
    for (size_t i = 0; i < faces.size(); i++)
    {
        pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
        text_lb = Point(faces[i].x, faces[i].y);
        if (pImage_roi[i].empty())
            continue;
        qDebug()<<"预测结果:"<<Predict(pImage_roi[i]);
        result = QString::number(Predict(pImage_roi[i]));
        str = result.toStdString();
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//所取的颜色任意值
        rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//放入缓存
        putText(frame, str, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));//添加文字
    }

    delete[]pImage_roi;

    Mat temp;
    cvtColor(frame, temp, CV_BGR2RGB);//BGR convert to RGB
//    QImage tempImage = QImage((const unsigned char*)(temp.data),
//                          temp.cols, temp.rows, temp.step,
//                          QImage::Format_RGB888);
    QImage tempImage(temp.data, temp.cols, temp.rows, temp.step1() , QImage::Format_RGB888);
    emit sigFaceResult(tempImage);
    msleep(10);
    emit sigIDResult(result);
    qDebug()<<"sigIDResult";
}
