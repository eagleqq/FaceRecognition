#ifndef FACEATTENDANCE_H
#define FACEATTENDANCE_H

#include <QMainWindow>
#include <iostream>
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include <fstream>
#include <sstream>
#include<math.h>
#include <QLabel>
#include <QTimer>
#include "admiwidget.h"
#include "basemainwindow.h"
#include "camerathread.h"
#include "face.hpp"

#include <QList>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "constants.h"
#include "showresultdialog.h"

using namespace std;
using namespace cv;


namespace Ui {
class FaceAttendance;
}

class FaceAttendance : public BaseMainWindow
{
    Q_OBJECT

public:
    explicit FaceAttendance(QWidget *parent = nullptr);
    ~FaceAttendance();
    void initWidget();
    QPixmap PixmapToRound(const QPixmap &src, int radius);
    void appendLog(const QString &text);
    bool isTimeValid(QString time);


private slots:
    void on_pushButton_break_clicked();
    void slotShowImage(QImage image);
    void slotShowIDResult(QString id);
    void showTime();
    void on_pushButton_cam_clicked();
    void on_pushButton_admi_clicked();
    void slotSetTimePeriod(QString b_time, QString e_time);

private:
    Ui::FaceAttendance *ui;
    QTimer *mUpdateTimeTimer;
    CameraThread *mCameraThread;
    QLabel *label_date_time;
    AdmiWidget *mAdmiWidget;

    QSqlDatabase db;
    ShowResultDialog *mShowResultDialog;

    QString mBeginTime;
    QString mEndTime;
};


#endif // FACEATTENDANCE_H
