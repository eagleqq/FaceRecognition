#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include "admiwidget.h"
#include "constants.h"
#include "passworddialog.h"
#include "sqlitesingleton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //初始化数据库
    sqliteSingleton::getInstance()->initDB("QSQLITE");
    sqliteSingleton::getInstance()->createTable();
    //管理员界面初始化
    AdmiWidget w;
    w.setWindowTitle("人脸识别后台管理系统");
    w.setSqlDatabase(sqliteSingleton::getInstance()->db);
    //密码输入界面
    PasswordDialog tPasswordDialog;
    tPasswordDialog.setPassword(sqliteSingleton::getInstance()->getAdmiPassword()); //获取数据库密码
    tPasswordDialog.exec();
    if(tPasswordDialog.getIsOk()){
        w.show(); //密码输入正确后，显示管理员界面
    }
    return a.exec();
}
