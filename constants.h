#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

const QString  PROJECT_PATH = ".";
const QString  ATT_FACES_PATH = PROJECT_PATH + "\\att_faces";
const QString  AT_TXT_PATH = ATT_FACES_PATH + "\\at.txt";
const QString  HAARCASCADE_FRONTALFACE_ALT2 = PROJECT_PATH + "\\tools\\haarcascade_frontalface_alt2.xml";

const QString  MyFacePCAModel_XML = PROJECT_PATH + "\\tools\\MyFacePCAModel.xml";
const QString  MyFaceFisherModel_XML = PROJECT_PATH + "\\tools\\MyFaceFisherModel.xml";
const QString  MyFaceLBPHModel_XML = PROJECT_PATH + "\\tools\\MyFaceLBPHModel.xml";

const int MAX_CAP_IMAGE_NUM = 10;  //最大采集图片数量
const int MAX_PROGRESS = MAX_CAP_IMAGE_NUM + 20;


//数据库配置
const QString HOST = "sh-cynosdbmysql-grp-3ychwa2k.sql.tencentcdb.com";
const QString USER = "root";
const QString PASSWORD = "zxcv@1234";
const QString DATABASE = "Face";
const int PORT= 29718;

#endif // CONSTANTS_H
