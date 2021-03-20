#ifndef SHOWRESULTDIALOG_H
#define SHOWRESULTDIALOG_H

#include <QDialog>

namespace Ui {
class ShowResultDialog;
}

class ShowResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowResultDialog(QWidget *parent = nullptr);
    ~ShowResultDialog();
    bool getIsOk();
    void setID(QString id);
    QString getID();
    void setName(QString name);
    QString getName();
    void setTime(QString time);
    QString getTime();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_sure_clicked();

private:
    Ui::ShowResultDialog *ui;
    bool isOk;
};

#endif // SHOWRESULTDIALOG_H
