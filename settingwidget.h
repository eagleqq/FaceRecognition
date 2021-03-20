#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QPaintEvent>
#include <QWidget>

namespace Ui {
class SettingWidget;
}

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

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
