#include "admiwidget.h"
#include "ui_admiwidget.h"
#include <QDebug>
#include <QPainter>

AdmiWidget::AdmiWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AdmiWidget)
{
    ui->setupUi(this);
    mSettingWidget = new SettingWidget(this);
    mRecordWidget = new RecordWidget(this);
    mFaceTrainWidget = new FaceTrainWidget(this);
    ui->stackedWidget->addWidget(mSettingWidget);
    ui->stackedWidget->addWidget(mRecordWidget);
    ui->stackedWidget->addWidget(mFaceTrainWidget);

    ui->stackedWidget->setCurrentWidget(mSettingWidget);
}

AdmiWidget::~AdmiWidget()
{
    delete ui;
}

void AdmiWidget::setSqlDatabase(QSqlDatabase db)
{
    mRecordWidget->setSqlDatabase(db);
}

void AdmiWidget::on_pushButton_setting_clicked()
{
    qDebug()<<"切换设置页面";
    ui->stackedWidget->setCurrentWidget(mSettingWidget);
}

void AdmiWidget::on_pushButton_face_clicked()
{
     qDebug()<<"切换人脸录入界面";
     ui->stackedWidget->setCurrentWidget(mFaceTrainWidget);
}

void AdmiWidget::on_pushButton_record_clicked()
{
    qDebug()<<"切换打卡记录界面";
    ui->stackedWidget->setCurrentWidget(mRecordWidget);
}

void AdmiWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.drawPixmap(rect(), QPixmap(":/images/bg.jpg"), QRect());
}

void AdmiWidget::on_pushButton_exit_clicked()
{
    this->close();
}
