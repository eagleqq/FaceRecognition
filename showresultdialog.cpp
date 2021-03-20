#include "showresultdialog.h"
#include "ui_showresultdialog.h"

#include <QPainter>

ShowResultDialog::ShowResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowResultDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowOpacity(0.9);//设置透明
    isOk = false;
}

ShowResultDialog::~ShowResultDialog()
{
    delete ui;
}

bool ShowResultDialog::getIsOk()
{
    return isOk;
}

void ShowResultDialog::setID(QString id)
{
    ui->lineEdit_id->setText(id);
}

QString ShowResultDialog::getID()
{
    return ui->lineEdit_id->text();
}

void ShowResultDialog::setName(QString name)
{
    ui->lineEdit_name->setText(name);
}

QString ShowResultDialog::getName()
{
    return ui->lineEdit_name->text();
}

void ShowResultDialog::setTime(QString time)
{
    ui->lineEdit_time->setText(time);
}

QString ShowResultDialog::getTime()
{
    return ui->lineEdit_time->text();
}

void ShowResultDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/images/bg2.jpg"), QRect());
}

void ShowResultDialog::on_pushButton_cancel_clicked()
{
    isOk = false;
    close();
}

void ShowResultDialog::on_pushButton_sure_clicked()
{
    isOk = true;
    close();
}
