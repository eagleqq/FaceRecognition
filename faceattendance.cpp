#include "faceattendance.h"
#include "ui_faceattendance.h"
#include "passworddialog.h"
#include "admiwidget.h"
#include "sqlitesingleton.h"

#include <QDateTime>
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QDateTime>
#include <QDateTime>

FaceAttendance::FaceAttendance(QWidget *parent) :
    BaseMainWindow(parent),
    ui(new Ui::FaceAttendance)
{
    ui->setupUi(this);

    initWidget();

    mUpdateTimeTimer = new QTimer(this);
    connect(mUpdateTimeTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    mUpdateTimeTimer->start(1000);

    mCameraThread = new CameraThread();
    connect(mCameraThread, &CameraThread::sigFaceResult, this, &FaceAttendance::slotShowImage);
    connect(mCameraThread, &CameraThread::sigIDResult, this, &FaceAttendance::slotShowIDResult);

    connect(mAdmiWidget->mSettingWidget, &SettingWidget::sigTimePeriod, this, &FaceAttendance::slotSetTimePeriod);

    appendLog("初始化系统");
}

FaceAttendance::~FaceAttendance()
{

    mCameraThread->isWork = false;
    mCameraThread->wait();
    delete ui;
}

void FaceAttendance::initWidget()
{
    mShowResultDialog = nullptr;
    mAdmiWidget = new AdmiWidget();
    this->setWindowIcon(QIcon(":/images/face5.png"));
    label_date_time = new QLabel(this);
    label_date_time->setStyleSheet("color: rgb(255, 255, 255);");
    ui->statusBar->addWidget(label_date_time);

    sqliteSingleton::getInstance()->initDB("QSQLITE");
    sqliteSingleton::getInstance()->createTable();
    mAdmiWidget->setSqlDatabase(sqliteSingleton::getInstance()->db);
}

void FaceAttendance::slotShowImage(QImage image)
{
    try {
        QPixmap mmp = QPixmap::fromImage(image);
        mmp = mmp.scaled(ui->label_face->size());
        mmp =  PixmapToRound(mmp, 148);
        ui->label_face->setScaledContents(true);
        ui->label_face->setPixmap(mmp);
        ui->label_face->show();
    } catch (exception ex) {
        qDebug() << "图片显示异常";
    }
    if(mCameraThread->isWork == false){
        ui->label_face->setPixmap(QPixmap());
        ui->label_face->clear();
    }
}

void FaceAttendance::slotShowIDResult(QString id)
{
    qDebug()<< "slotShowIDResult";
    QString name = sqliteSingleton::getInstance()->getStudentName(id);
    //数据库中有
    if(!name.isEmpty()){
        mCameraThread->isWork = false;
        if(mShowResultDialog == nullptr)
            mShowResultDialog = new ShowResultDialog();
        mShowResultDialog->setID(id);
        mShowResultDialog->setName(name);
        QDateTime local(QDateTime::currentDateTime());
        mShowResultDialog->setTime(local.toString("yyyy-MM-dd hh:mm:ss"));
        mShowResultDialog->exec();
        if(mShowResultDialog->getIsOk()){
            bool isValid = isTimeValid(local.toString("hh:mm:ss"));
            if(isValid){
                sqliteSingleton::getInstance()->insertRecordTable(id, name,
                                                                  local.toString("yyyy-MM-dd"),
                                                                  local.toString("hh:mm:ss"),
                                                                  "有效");
                appendLog(name + "在规定时间完成打卡");
            }else{
                sqliteSingleton::getInstance()->insertRecordTable(id, name,
                                                                  local.toString("yyyy-MM-dd"),
                                                                  local.toString("hh:mm:ss"),
                                                                  "无效");
                appendLog(name + "在非规定时间打卡");
            }

        }
        delete mShowResultDialog;
        mShowResultDialog = nullptr;
        mCameraThread->isWork = true;
        mCameraThread->start();
    }
}

void FaceAttendance::showTime()
{
    QDateTime local(QDateTime::currentDateTime());
    label_date_time->setText(local.toString("yyyy年MM月dd日  hh:mm:ss"));
}

/**
 * @brief 退出系统
 */

void FaceAttendance::on_pushButton_break_clicked()
{
    mCameraThread->isWork=false;
    this->close();
}

QPixmap FaceAttendance::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 150, 150);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

void FaceAttendance::appendLog(const QString &text)
{
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd hh:mm:ss  ");
    ui->textBrowserLog->append(localTime + text);
}

bool FaceAttendance::isTimeValid(QString time)
{
    if(mBeginTime.isEmpty() || mEndTime.isEmpty()){
        return true;
    }
    qDebug()<<"打开时间="<<time;
    qDebug()<<mBeginTime<<mEndTime;
    if(time > mBeginTime && time < mEndTime){
        return true;
    }
    return false;
}

void FaceAttendance::on_pushButton_cam_clicked()
{
   static bool isOpen=false;
   if(isOpen){
       mCameraThread->isWork = false;
       isOpen = false;
       ui->pushButton_cam->setStyleSheet(
                   "border-image: url(:/images/cam-off.png);");
       ui->label_face->setPixmap(QPixmap());
       ui->label_face->clear();
   }else{
       mCameraThread->start();
       isOpen = true;
       ui->pushButton_cam->setStyleSheet(
                   "border-image: url(:/images/cam-on.png);");
   }
}

void FaceAttendance::on_pushButton_admi_clicked()
{
    PasswordDialog tPasswordDialog;
//    tPasswordDialog.setPassword(getAdmiPassword());
    tPasswordDialog.setPassword(sqliteSingleton::getInstance()->getAdmiPassword());
    tPasswordDialog.exec();
    if(tPasswordDialog.getIsOk()){
        mAdmiWidget->setWindowModality(Qt::ApplicationModal);//设置模态
        mAdmiWidget->show();
    }
}

void FaceAttendance::slotSetTimePeriod(QString b_time, QString e_time)
{
    appendLog(tr("设置打卡时间段: %1 ~ %2").arg(b_time).arg(e_time));
    mBeginTime = b_time;
    mEndTime = e_time;
}
