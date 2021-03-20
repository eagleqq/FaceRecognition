#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    ~PasswordDialog();
    bool getIsOk();
    void setPassword(QList<QString> pwd);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_num0_clicked();

    void on_num1_clicked();

    void on_num2_clicked();

    void on_num3_clicked();

    void on_num4_clicked();

    void on_num5_clicked();

    void on_num6_clicked();

    void on_num7_clicked();

    void on_num8_clicked();

    void on_num9_clicked();

    void on_delbt_clicked();

    void on_endbt_clicked();

private:
    Ui::PasswordDialog *ui;
    bool isOk; //密码输入是否正确
    QList<QString> mPwdList;
};

#endif // PASSWORDDIALOG_H
