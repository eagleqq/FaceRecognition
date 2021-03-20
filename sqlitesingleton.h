#ifndef SQLITESINGLETON_H
#define SQLITESINGLETON_H
#include <QMutexLocker>
#include <QSharedPointer>
#include <QObject>
#include <QMutex>
#include <QDebug>
#include <QSqlDatabase>

class sqliteSingleton: public QObject
{
    Q_OBJECT
public:
    static sqliteSingleton *getInstance()
    {
        if(m_pInstance == NULL)
        {
            QMutexLocker mlocker(&m_mutex);
            if(m_pInstance == NULL)
            {
                m_pInstance = new sqliteSingleton();
            }
        }
        return m_pInstance;
    }

    void initDB(QString db_type);
    void createTable();
    void insertAdmiTable(QString id, QString pwd);
    void insertStuTable(QString id, QString name);
    void insertRecordTable(QString stu_id, QString name,QString clock_date, QString clock_time, QString valid);

    QString getStudentName(QString id);
    QList<QString> getAdmiPassword();


private:
    explicit sqliteSingleton(QObject *parent = 0);//构造函数
    sqliteSingleton(const sqliteSingleton &,QObject *parent = 0): QObject(parent) {}//拷贝构造函数
    sqliteSingleton& operator =(const sqliteSingleton&){return *this;}//赋值操作符重写
    static sqliteSingleton* m_pInstance;//定义单例指针
    static QMutex m_mutex;//互斥锁
public:
    QSqlDatabase db;

public:
    class Garbo     //专门用来析构m_pInstance指针的类
    {
    public:
        ~Garbo()
        {
            if(m_pInstance != NULL)
            {
                delete m_pInstance;
                m_pInstance = NULL;
                qDebug()<<"["<<__FILE__<<"]"<<__LINE__<<__FUNCTION__<<"m_pInstance 被析构";
            }
        }
    };
    static Garbo m_garbo;
};

#endif // SQLITESINGLETON_H
