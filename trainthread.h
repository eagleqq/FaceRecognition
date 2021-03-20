#ifndef TRAIN_H
#define TRAIN_H

#include "face.hpp"
#include <QThread>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;
using namespace cv;

#define SEPARATOR ';'

class TrainThread:public QThread
{
    Q_OBJECT
signals:
    void sigFinished();
    void sigFailed();

public:
    explicit TrainThread(QObject *parent = nullptr);
    ~TrainThread();
    void run();
    void train();
    void read_csv(const string &, vector<Mat> &, vector<int> &, char);
};

#endif // TRAIN_H
