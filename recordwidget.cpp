#include "recordwidget.h"
#include "ui_recordwidget.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRecord>
#include "constants.h"
#include "sqlitesingleton.h"

RecordWidget::RecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::setSqlDatabase(QSqlDatabase db)
{
    this->db = db;
    mSQLModel = new QSqlTableModel(this, this->db);
    mSQLModel->setTable("record_info");
    mSQLModel->setHeaderData(0,Qt::Horizontal,tr("序号"));
    mSQLModel->setHeaderData(1,Qt::Horizontal,tr("学号"));
    mSQLModel->setHeaderData(2,Qt::Horizontal,tr("姓名"));
    mSQLModel->setHeaderData(3,Qt::Horizontal,tr("打卡日期"));
    mSQLModel->setHeaderData(4,Qt::Horizontal,tr("打卡时间"));
    mSQLModel->setHeaderData(5,Qt::Horizontal,tr("是否有效"));
    mSQLModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(mSQLModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//设置最后一列填充后面表格
    ui->tableView->setColumnHidden(0,true);//设置第0列隐藏
    ui->tableView->setColumnWidth(3,200);//设置列宽，界面看起来更舒适
    mSQLModel->select(); //选取整个表的所有行
}

void RecordWidget::on_pushButton_search_clicked()
{
    QString idFilter="";
    QString timeFilter="";
    idFilter = tr("stuId = '%1'").arg(ui->lineEditID->text().toInt());
    mSQLModel->setFilter(idFilter);
    timeFilter = tr("clockDate = '%1'").arg(ui->dateEditTime->text());
    qDebug()<< idFilter << timeFilter;
    mSQLModel->setFilter(timeFilter);
    mSQLModel->select(); //显示结果
}


void RecordWidget::on_pushButtonExport_clicked()
{
    QDir dir;
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Open Excel"),
            "",
            tr("Excel Files (*.csv)"));
    if (!fileName.isNull())
    {
        //fileName是文件名
        qDebug()<<fileName;
        QFile file(fileName);            // 以上两行用时间戳作为文件名
        if(file.open(QFile::WriteOnly | QFile::Truncate))        // 打开文件
        {
            QTextStream out(&file);    // 输入流
            int row = mSQLModel->rowCount();
            int col = mSQLModel->columnCount();
            for(int i=0; i<row; i++){
                for(int j=0; j<col; j++){
                    QString value = mSQLModel->record(i).value(j).toString() + ",";
                    out << value;
                }
                out << "\n";
            }
        }
        file.close();
        QMessageBox::information(NULL, "提示", "导出成功！\n导出路径：" +fileName);
    }
}
