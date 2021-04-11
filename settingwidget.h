#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QPaintEvent>
#include <QWidget>

namespace Ui {
class SettingWidget;
}
//设置页面
class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

signals:
    void sigTimePeriod(QString begin_time, QString end_time);

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
