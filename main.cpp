#include "faceattendance.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include "constants.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //人脸识别界面
    FaceAttendance w;
    w.show();

    return a.exec();
}
