#-------------------------------------------------
#
# Project created by QtCreator 2021-05-06T21:30:50
#
#-------------------------------------------------

QT+= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = veges
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
CONFIG += no_keywords
QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/lib/opencv
LIBS += `pkg-config --libs opencv`
#INCLUDEPATH +=$$PWD/../jsoncpp

INCLUDEPATH += $$PWD/../libtorch/include \
              $$PWD/../libtorch/include/torch/csrc/api/include
DEPENDPATH += $$PWD/../libtorch/include \
            $$PWD/../libtorch/include/torch/csrc/api/include
#include(/mnt/hgfs/vmgx/vege/ourvege/vege1.0/veges/jsoncpp/jsoncpp.pri)
LIBS += -L$$PWD/../libtorch/lib -lc10 \
 -lcaffe2_detectron_ops \
-lcaffe2_module_test_dynamic \
-lclog -lcpuinfo  \
-ltorch

LIBS += -lopencv_core\
-lopencv_imgproc\
-lopencv_highgui\
-lopencv_ml\
-lopencv_video\
-lopencv_features2d\
-lopencv_calib3d\
-lopencv_objdetect\
#-lopencv_legacy\
-lopencv_flann\

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    drawing.cpp \
    dialogw.cpp \
   



HEADERS += \
        mainwindow.h \
    drawing.h \
    header.h \
    dialogw.h \





FORMS += \
        mainwindow.ui \
    drawing.ui \
    dialogw.ui


DISTFILES += \
    coin/OIP.jpg \
    themes/darkblack.qss \
    themes/gray.qss \
    themes/light.qss \
    model/char_js.json \
    model/char_utf.json \
    model/model.pt \



