#include "faceattendance.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include "constants.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString fileName = QCoreApplication::applicationDirPath();
    qDebug()<<fileName;
    qDebug() << QDir::toNativeSeparators(fileName);
    FaceAttendance w;
    w.show();

    return a.exec();
}
