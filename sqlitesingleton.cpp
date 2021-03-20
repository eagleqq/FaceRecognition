#include "sqlitesingleton.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <constants.h>

sqliteSingleton* sqliteSingleton::m_pInstance = NULL;
sqliteSingleton::Garbo m_Garbo;
QMutex sqliteSingleton::m_mutex;

sqliteSingleton::sqliteSingleton(QObject *parent)
{

}

void sqliteSingleton::initDB(QString db_type)
{
    qDebug() << "初始化数据库";
    if(db_type == "QSQLITE"){
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("myface.dat");
        if (!db.open()) {
            QSqlError lastError = db.lastError();
            QMessageBox::warning(0, QObject::tr("Database Error"),
                                 "数据库打开失败," + lastError.driverText());
            return ;
        }
    }else if(db_type == "QMYSQL"){
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(HOST);
        db.setDatabaseName(DATABASE);       //这里输入你的数据库名
        db.setUserName(USER);
        db.setPassword(PASSWORD);   //这里输入你的密码
        db.setPort(PORT);
        if (!db.open()) {
            QSqlError lastError = db.lastError();
            QMessageBox::warning(0, QObject::tr("Database Error"),
                                 "数据库打开失败," + lastError.driverText());
            return ;
        }
    }
}

void sqliteSingleton::createTable()
{
    QSqlQuery query(db);
    bool ret = query.exec("create table admi_info (id varchar(40) primary key, password varchar(20))");
    qDebug() << "创建管理员信息表格admi_info" << ret;

    ret = query.exec("create table stu_info (id varchar(40) primary key, name varchar(20))");
    qDebug() << "创建学生信息表格stu_info" << ret;

    ret = query.exec("create table record_info (id int primary key, stuId int, name varchar(20), clockDate varchar(40),clockTime varchar(40), isValid varchar(80))");
    qDebug() << "创建打卡记录表格record_info" << ret;

    insertAdmiTable("1", "654321");
    insertStuTable("2016117249", "shenjun");
    insertRecordTable("17310520301", "fangjun", "", "", "无效");
}

void sqliteSingleton::insertAdmiTable(QString id, QString pwd)
{
    QSqlQuery query(db);
    bool ret = query.exec(tr("insert into admi_info values('%1', '%2')").arg(id).arg(pwd));
    qDebug() << "insertAdmiTable" << ret;
}

void sqliteSingleton::insertStuTable(QString id, QString name)
{
    QSqlQuery query(db);
    bool ret = query.exec(tr("insert into stu_info values('%1', '%2')").arg(id).arg(name));
    qDebug() << "insertStuTable" << ret;
}

void sqliteSingleton::insertRecordTable(QString stu_id, QString name,
                                        QString clock_date, QString clock_time, QString valid)
{
    QSqlQuery query(db);
    bool ret = query.exec(tr("insert into record_info(stuId, name, clockDate, clockTime, isValid) "
                             "values('%1', '%2', '%3', '%4','%5')")
                          .arg(stu_id)
                          .arg(name)
                          .arg(clock_date)
                          .arg(clock_time)
                          .arg(valid));
    qDebug() << "insertRecordTable" << ret;
}

QString sqliteSingleton::getStudentName(QString id)
{
    QString name;
    QSqlQuery query(db);
    bool ret = query.exec(tr("select * from stu_info where id='%1'").arg(id));
    qDebug() << "getStudentName" << ret;
    while (query.next()) {
        name = query.value("name").toString();
        qDebug()<<name;
    }
    return name;
}

QList<QString> sqliteSingleton::getAdmiPassword()
{
    QList<QString> pwdList;
    QSqlQuery query(db);
    bool ret = query.exec(tr("select * from admi_info"));
    qDebug() << "getAdmiPassword" << ret;
    while (query.next()) {
        pwdList.append(query.value("password").toString());
    }
    return pwdList;
}


