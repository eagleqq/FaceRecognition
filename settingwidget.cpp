#include "settingwidget.h"
#include "ui_settingwidget.h"

#include <QMessageBox>
#include <QPainter>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::on_pushButton_save_clicked()
{
    QString begin_time = ui->timeEdit_begin->text();
    QString end_time = ui->timeEdit_end->text();
    if(end_time > begin_time){
        emit sigTimePeriod(begin_time, end_time);
        QMessageBox::information(NULL, "提示", "设置成功！");
    }else{
        QMessageBox::information(NULL, "提示", "结束时间必须大于开始时间！");
    }
}
