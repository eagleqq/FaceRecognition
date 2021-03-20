#include "facetrainwidget.h"
#include "ui_facetrainwidget.h"
#include "constants.h"
#include "sqlitesingleton.h"

#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QStandardItemModel>

FaceTrainWidget::FaceTrainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceTrainWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    updateTableData();

    mCapTimer = new QTimer;
    connect(mCapTimer, SIGNAL(timeout()), this, SLOT(showImage()));//时间到后启动opencam时间
    mTrainThread = new TrainThread(this);//训练线程
    connect(mTrainThread, SIGNAL(sigFinished()), this, SLOT(slotTrainFinished()));
    connect(mTrainThread, SIGNAL(sigFailed()), this, SLOT(slotTrainFailed()));

    //装载人脸识别分类器
    cascada.load(HAARCASCADE_FRONTALFACE_ALT2.toStdString());
}

FaceTrainWidget::~FaceTrainWidget()
{
    if ( mTrainThread->isRunning() )
    {
        mTrainThread->wait();
    }
    delete ui;
}

QList<QString> FaceTrainWidget::getAllFileFolder(QString dirPath)
{
    QList<QString> folderList;
    QDir dir(dirPath);
    dir.setFilter(QDir::Dirs);
    foreach(QFileInfo fullDir, dir.entryInfoList())
    {
        if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
        folderList.append(fullDir.fileName());
    }
    return folderList;
}

void FaceTrainWidget::updateTableData()
{
    QList<QString> list = getAllFileFolder(ATT_FACES_PATH);
    qDebug()<<list;
    int row = 0;
    ui->tableWidget->setRowCount(list.length());
    foreach (QString id, list) {
     qDebug()<<id;
     QTableWidgetItem   *item;
     item = new QTableWidgetItem(id);
     item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
     ui->tableWidget->setItem(row,0,item); //为单元格设置Item
     item = new QTableWidgetItem(ATT_FACES_PATH + "\\" + id);
     item->setToolTip(ATT_FACES_PATH + "\\" + id);
     ui->tableWidget->setItem(row,1,item); //为单元格设置Item
     row ++;
    }
}

bool FaceTrainWidget::DeleteFileOrFolder(const QString &strPath)
{
    if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo FileInfo(strPath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(strPath);
    else if (FileInfo.isDir())//如果是文件夹
    {
        QDir qDir(strPath);
        qDir.removeRecursively();
    }
    return true;
}

void FaceTrainWidget::CreateCSV()
{
    QList<QString> list = getAllFileFolder(ATT_FACES_PATH);
    qDebug()<<list;
    DeleteFileOrFolder(AT_TXT_PATH);
    QFile file(AT_TXT_PATH);
    file.open(QIODevice::ReadWrite | QIODevice::Text);  //打开文件，不存在则创建
    QString img_type = ".jpg";
    foreach (QString id, list) {
//        if(id[0] == "s" ){
//            img_type = ".pgm";
//        }else{
//            img_type = ".jpg";
//        }
     for(int i=1;i<=MAX_CAP_IMAGE_NUM;i++) {
        QString str= ATT_FACES_PATH + "\\" + id
                + "/" + QString::number(i)+  img_type + ";"+id;
        //写入文件需要字符串为QByteArray格式
        file.write(str.toUtf8() + "\n");
     }
    }
    file.close();
}

void FaceTrainWidget::on_pushButton_add_clicked()
{
//    pic_num = 0;
    QString id = ui->lineEdit_num->text();
    QString name = ui->lineEdit_name->text();
    if(id.isEmpty()){
        QMessageBox::information(NULL, "提示", "请输入学号！");
        return;
    }
    if(name.isEmpty()){
        QMessageBox::information(NULL, "提示", "请输入姓名！");
        return;
    }
    QList<QString> list = getAllFileFolder(ATT_FACES_PATH);
    qDebug()<<list;
    if(list.contains(id)){
        QMessageBox::warning(NULL, "提示", "该学号已经存在！");
        return;
    }
    QString distPath = ATT_FACES_PATH + "//"+ id;
    qDebug()<<distPath;
    QDir dir;
    bool res = dir.mkpath(distPath);
    if(res){
        sqliteSingleton::getInstance()->insertStuTable(id,name);
        QMessageBox::information(NULL, "提示", "添加成功");
    }
    else{
        QMessageBox::warning(NULL, "提示", "添加失败");
    }
    updateTableData();
}

void FaceTrainWidget::on_pushButton_del_clicked()
{
    QModelIndex index = ui->tableWidget->selectionModel()->currentIndex();
    int row = index.row();
    if(row <=-1){
        QMessageBox::information(NULL, "提示", "请选中一行！");
        return;
    }
    qDebug()<<row;
    QString id = ui->tableWidget->item(row,0)->text();
    QString path = ui->tableWidget->item(row,1)->text();

    QString sql = QString ("delete from staff_info where id='%1'").arg(id);
    QSqlQuery query(sql);
    bool del_ret = DeleteFileOrFolder(path);
    if(del_ret){
      QMessageBox::information(NULL, "提示", "已删除学号："+id);
    }else{
      QMessageBox::warning(NULL, "提示", "删除失败！");
    }
    updateTableData();
}

void FaceTrainWidget::on_pushButton_find_clicked()
{
    updateTableData();
}

void FaceTrainWidget::on_pushButton_cap_clicked()
{
    QModelIndex index = ui->tableWidget->selectionModel()->currentIndex();
    int row = index.row();
    if(row <=-1){
        QMessageBox::information(NULL, "提示", "请选中一行！");
        return;
    }
    pic_num = 0;
    cap.open(0);
    mCapTimer->start(1000);
    ui->progressBarTrain->setMaximum(MAX_PROGRESS);
    ui->progressBarTrain->setValue(0);
}

void FaceTrainWidget::showImage()
{
//    cap.open(0);
    Mat temp;//临时保存RGB图像
    cap>>frame;//摄像头读取头像
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);//转灰度化，减少运算
    cascada.detectMultiScale(frame_gray, faces, 1.1, 4,
                             CV_HAAR_DO_ROUGH_SEARCH,
                             Size(70, 70),
                             Size(1000, 1000));
    ui->label_tip->setText("检测到人脸个数=" + QString::number(faces.size()));
    qDebug()<<"检测到人脸个数:" + QString::number(faces.size());
    //识别到的脸用矩形圈出
    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
    }

    cvtColor(frame, temp, CV_BGR2RGB);//BGR convert to RGB
    QImage Qtemp = QImage((const unsigned char*)(temp.data),
                          temp.cols, temp.rows, temp.step,
                          QImage::Format_RGB888);
    ui->label_face->setScaledContents(true);
    ui->label_face->setPixmap(QPixmap::fromImage(Qtemp));
    //当只有一个人脸时，开始拍照
    if (faces.size() == 1)
    {
        pic_num ++;
        ui->label_tip->setText("已经采集头像第" + QString::number(pic_num) + "张");
        Mat faceROI = frame_gray(faces[0]);//在灰度图中将圈出的脸所在区域裁剪出
        ::resize(faceROI, myFace, Size(92, 112));//将兴趣域size为92*112
        //在 faces[0].tl()的左上角上面写序号
        putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);
        Mat temp;//临时保存RGB图像
        cvtColor(frame, temp, CV_BGR2RGB);//BGR convert to RGB
        QImage Qtemp = QImage((const unsigned char*)(temp.data),
                              temp.cols, temp.rows, temp.step,
                              QImage::Format_RGB888);
        //图片的存放位置
        QModelIndex index = ui->tableWidget->selectionModel()->currentIndex();
        int row = index.row();
        QString image_path = ui->tableWidget->item(row,1)->text() +
                "\\" + QString::number(pic_num) + ".jpg";
        image_path = QDir::toNativeSeparators(image_path);
        string filename = image_path.toStdString();
        imwrite(filename, myFace);//存在当前目录下
        ui->progressBarTrain->setValue(pic_num);
        if(pic_num >= MAX_CAP_IMAGE_NUM){
            ui->label_tip->setText("采集完毕，生成训练文件");
            mCapTimer->stop();
            cap.release();
            //生成训练文件
            CreateCSV();
            //训练
            this->setEnabled(false);
            mTrainThread->start();
        }
    }
}

void FaceTrainWidget::slotTrainFinished()
{
    this->setEnabled(true);
    ui->label_tip->setText("训练完成");
    ui->progressBarTrain->setValue(MAX_PROGRESS);
    QMessageBox::information(NULL, "提示", "训练完成！");
}

void FaceTrainWidget::slotTrainFailed()
{
    this->setEnabled(true);
    QMessageBox::information(NULL, "提示", "训练失败！");
}
