#include "passworddialog.h"
#include "ui_passworddialog.h"

#include <QMessageBox>
#include <QPainter>

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    isOk = false;
    this->setWindowIcon(QIcon(":/images/face5.png"));
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

bool PasswordDialog::getIsOk()
{
    return isOk;
}

void PasswordDialog::setPassword(QList<QString> pwd)
{
    mPwdList = pwd;
}

void PasswordDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.drawPixmap(rect(), QPixmap(":/images/bg2.jpg"), QRect());
}

void PasswordDialog::on_num0_clicked()
{
    QString text = ui->pressedit->text();
    text.append("0");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num1_clicked()
{
    QString text = ui->pressedit->text();
    text.append("1");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num2_clicked()
{
    QString text = ui->pressedit->text();
    text.append("2");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num3_clicked()
{
    QString text = ui->pressedit->text();
    text.append("3");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num4_clicked()
{
    QString text = ui->pressedit->text();
    text.append("4");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num5_clicked()
{
    QString text = ui->pressedit->text();
    text.append("5");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num6_clicked()
{
    QString text = ui->pressedit->text();
    text.append("6");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num7_clicked()
{
    QString text = ui->pressedit->text();
    text.append("7");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num8_clicked()
{
    QString text = ui->pressedit->text();
    text.append("8");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_num9_clicked()
{
    QString text = ui->pressedit->text();
    text.append("9");
    ui->pressedit->setText(text);
}

void PasswordDialog::on_delbt_clicked()
{
    QString text = ui->pressedit->text();
    text.remove(text.size()-1, 1);//删除最后一个字符
    ui->pressedit->setText(text);
}

void PasswordDialog::on_endbt_clicked()
{
    QString text = ui->pressedit->text();
    if(mPwdList.contains(text)){
        isOk = true;
        this->close();
    }else{
        isOk = false;
        QMessageBox::information(this, "提示", "密码验证失败");
    }
}
