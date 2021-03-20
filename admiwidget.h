#ifndef ADMIWIDGET_H
#define ADMIWIDGET_H

#include "basewidget.h"
#include "facetrainwidget.h"
#include "recordwidget.h"
#include "settingwidget.h"

#include <QWidget>

namespace Ui {
class AdmiWidget;
}

class AdmiWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit AdmiWidget(QWidget *parent = nullptr);
    ~AdmiWidget();
    void setSqlDatabase(QSqlDatabase db);

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_face_clicked();

    void on_pushButton_record_clicked();

    void on_pushButton_exit_clicked();

protected:
    void paintEvent(QPaintEvent *event);

public:
    SettingWidget *mSettingWidget;
    RecordWidget *mRecordWidget;
    FaceTrainWidget *mFaceTrainWidget;

private:
    Ui::AdmiWidget *ui;

};

#endif // ADMIWIDGET_H
