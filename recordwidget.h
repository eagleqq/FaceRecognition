#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QSqlTableModel>
#include <QWidget>

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecordWidget(QWidget *parent = nullptr);
    ~RecordWidget();
    void setSqlDatabase(QSqlDatabase db);

private slots:
    void on_pushButton_search_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_search_time_clicked();

private:
    Ui::RecordWidget *ui;
    QSqlDatabase db;
    QSqlTableModel *mSQLModel;
};

#endif // RECORDWIDGET_H
