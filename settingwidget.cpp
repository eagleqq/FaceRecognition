#include "settingwidget.h"
#include "sqlitesingleton.h"
#include "ui_settingwidget.h"

#include <QMessageBox>
#include <QPainter>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    ui->lineEdit_title->setText("好好学习，天天向上");
    ui->textEdit_context->setText("读书、锻炼、做公益");
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
        QMessageBox::information(this, "提示", "设置成功！");
    }else{
        QMessageBox::information(this, "提示", "结束时间必须大于开始时间！");
    }
}

void SettingWidget::on_pushButton_send_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString context = ui->textEdit_context->toPlainText();
    if(title.isEmpty()){
         QMessageBox::information(this, "提示", "标题不能为空！");
         return;
    }
    if(context.isEmpty()){
       QMessageBox::information(this, "提示", "内容不能为空！");
       return;
    }
    bool ret = sqliteSingleton::getInstance()->insertNoticeTable(title, context);
    if(ret){
        QMessageBox::information(this, "提示", "发布成功！");
    }else{
        QMessageBox::information(this, "提示", "发布失败！");
    }

}
