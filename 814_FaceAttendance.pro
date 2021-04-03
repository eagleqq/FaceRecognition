#-------------------------------------------------
#
# Project created by QtCreator 2019-08-14T11:10:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 814_FaceAttendance
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
# 添加src目录下的源文件
SOURCES += \
        main.cpp \
    src/bif.cpp \
    src/eigen_faces.cpp \
    src/face_alignment.cpp \
    src/face_basic.cpp \
    src/facemark.cpp \
    src/facemarkAAM.cpp \
    src/facemarkLBF.cpp \
    src/facerec.cpp \
    src/fisher_faces.cpp \
    src/getlandmarks.cpp \
    src/lbph_faces.cpp \
    src/mace.cpp \
    src/predict_collector.cpp \
    src/regtree.cpp \
    src/trainFacemark.cpp \
    camerathread.cpp \
    passworddialog.cpp \
    admiwidget.cpp \
    settingwidget.cpp \
    recordwidget.cpp \
    facetrainwidget.cpp \
    basewidget.cpp \
    basemainwindow.cpp \
    trainthread.cpp \
    sqlitesingleton.cpp

HEADERS += \
    face/bif.hpp \
    face/face_alignment.hpp \
    face/facemark.hpp \
    face/facemark_train.hpp \
    face/facemarkAAM.hpp \
    face/facemarkLBF.hpp \
    face/facerec.hpp \
    face/mace.hpp \
    face/predict_collector.hpp \
    src/face_alignmentimpl.hpp \
    src/face_utils.hpp \
    src/precomp.hpp \
    face.hpp \
    camerathread.h \
    passworddialog.h \
    admiwidget.h \
    settingwidget.h \
    recordwidget.h \
    facetrainwidget.h \
    constants.h \
    basewidget.h \
    basemainwindow.h \
    trainthread.h \
    sqlitesingleton.h

FORMS += \
    passworddialog.ui \
    admiwidget.ui \
    settingwidget.ui \
    recordwidget.ui \
    facetrainwidget.ui


INCLUDEPATH +=D:\opencv64\include
INCLUDEPATH +=D:\opencv64\include\opencv
INCLUDEPATH +=D:\opencv64\include\opencv2

LIBS += D:\opencv64\x64\mingw\lib\libopencv*

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    creat_csv.py

RESOURCES += \
    im.qrc


