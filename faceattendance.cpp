#include "faceattendance.h"
#include "ui_faceattendance.h"
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

    mUpdateTimeTimer = new QTimer(this);   //刷新时间定时器
    connect(mUpdateTimeTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    mUpdateTimeTimer->start(1000);

    mCameraThread = new CameraThread();  //相机读取线程，包含料人脸识别
    connect(mCameraThread, &CameraThread::sigFaceResult, this, &FaceAttendance::slotShowImage);
    connect(mCameraThread, &CameraThread::sigIDResult, this, &FaceAttendance::slotShowIDResult);

//    connect(mAdmiWidget->mSettingWidget, &SettingWidget::sigTimePeriod, this, &FaceAttendance::slotSetTimePeriod);

    appendLog("初始化系统");
    ui->pushButton_admi->setVisible(false);
}

FaceAttendance::~FaceAttendance()
{

    mCameraThread->isWork = false;
    mCameraThread->wait();
    delete ui;
}

void FaceAttendance::initWidget()
{
    this->setWindowIcon(QIcon(":/images/face5.png"));
    label_date_time = new QLabel(this);
    label_date_time->setStyleSheet("color: rgb(255, 255, 255);");
    ui->statusBar->addWidget(label_date_time);

    sqliteSingleton::getInstance()->initDB("QSQLITE");
    sqliteSingleton::getInstance()->createTable();
}

//显示图片
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
//显示识别结果
void FaceAttendance::slotShowIDResult(QString id)
{
    qDebug()<< "slotShowIDResult";
    QString name = sqliteSingleton::getInstance()->getStudentName(id);
    //数据库中有
    ui->lineEdit_id->setText(id);
    ui->lineEdit_name->setText("");
    if(!name.isEmpty()){
        ui->lineEdit_name->setText(name);
    }
}
//确定打卡
void FaceAttendance::on_pushButton_sure_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString name = ui->lineEdit_name->text();
    if(id.isEmpty() || name.isEmpty()){
        appendLog("没有检测结果无法打卡");
        return;
    }
    QDateTime local(QDateTime::currentDateTime());
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

//显示时间
void FaceAttendance::showTime()
{
    QDateTime local(QDateTime::currentDateTime());
    label_date_time->setText(local.toString("yyyy年MM月dd日  hh:mm:ss"));
//    ui->textBrowserNotice->setText("通告标题：好好学习，天天向上 \n通告内容：读书、锻炼、做公益");
    QString title = sqliteSingleton::getInstance()->getNoticeTitle();
    QString context = sqliteSingleton::getInstance()->getNoticeContext();
    ui->textBrowserNotice->setText(tr("通告标题：%1 \n通告内容：%2").arg(title).arg(context));
}

/**
 * @brief 退出系统
 */

void FaceAttendance::on_pushButton_break_clicked()
{
    mCameraThread->isWork=false;
    this->close();
}

//图片截取成圆形
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

//添加日志
void FaceAttendance::appendLog(const QString &text)
{
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd hh:mm:ss  ");
    ui->textBrowserLog->append(localTime);
    ui->textBrowserLog->append(text);
}

//判断时间是否有效
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

//打开摄像头
void FaceAttendance::on_pushButton_cam_clicked()
{
   static bool isOpen=false;
   if(isOpen){
       appendLog("关闭摄像头");
       mCameraThread->isWork = false;
       isOpen = false;
       ui->pushButton_cam->setStyleSheet(
                   "border-image: url(:/images/cam-off.png);");
       ui->label_face->setPixmap(QPixmap());
       ui->label_face->clear();
   }else{
       appendLog("打开摄像头");
       mCameraThread->start();
       isOpen = true;
       ui->pushButton_cam->setStyleSheet(
                   "border-image: url(:/images/cam-on.png);");
   }
}

void FaceAttendance::on_pushButton_admi_clicked()
{
//    PasswordDialog tPasswordDialog;
//    tPasswordDialog.setPassword(getAdmiPassword());
//    tPasswordDialog.setPassword(sqliteSingleton::getInstance()->getAdmiPassword());
//    tPasswordDialog.exec();
//    if(tPasswordDialog.getIsOk()){
//        mAdmiWidget->setWindowModality(Qt::ApplicationModal);//设置模态
//        mAdmiWidget->show();
//    }
}

void FaceAttendance::slotSetTimePeriod(QString b_time, QString e_time)
{
    appendLog(tr("设置打卡时间段: %1 ~ %2").arg(b_time).arg(e_time));
    mBeginTime = b_time;
    mEndTime = e_time;
}
