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
    sqliteSingleton::getInstance()->initDB("QSQLITE");
    sqliteSingleton::getInstance()->createTable();
    AdmiWidget w;
    w.setWindowTitle("人脸识别后台管理系统");
    w.setSqlDatabase(sqliteSingleton::getInstance()->db);

    PasswordDialog tPasswordDialog;
    tPasswordDialog.setPassword(sqliteSingleton::getInstance()->getAdmiPassword());
    tPasswordDialog.exec();
    if(tPasswordDialog.getIsOk()){
        w.show();
    }
    return a.exec();
}
