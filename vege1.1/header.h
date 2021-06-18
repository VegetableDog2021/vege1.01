#ifndef HEADER_H
#define HEADER_H
#undef slots
#include <torch/script.h>
#include <torch/torch.h>
#define slots Q_SLOTS
#include <QString>
#include<QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QResizeEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QWidget>

#include <QThread>
#include <QFrame>
#include <QApplication>
#include <QCloseEvent>
#include <QColor>
#include <QDesktopServices>
#include <QIcon>
#include <QLabel>
#include <QUrl>
#include <QPlainTextEdit>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <jsoncpp/json/json.h>

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>

using namespace cv;
using namespace cv::ml;
using namespace std;

//cv::Mat转换为QImage
inline QImage toQImage(Mat img){
    QImage qimg=QImage(static_cast<unsigned char*>(img.data),
                       img.cols,img.rows,img.cols*img.channels(),QImage::Format_RGB888);
    return qimg;
}
//QImage转换为cv::Mat
inline Mat toMat(QImage image){
    Mat mat;
    if(image.format() == QImage::Format_ARGB32 || image.format() == QImage::Format_RGB32||image.format() == QImage::Format_ARGB32_Premultiplied){
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
    }else if(image.format() == QImage::Format_RGB888){
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, COLOR_BGR2RGB);
    }else if(image.format()== QImage::Format_Indexed8){
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
    }
    return mat;
}
//将图片处理为灰度图
inline cv::Mat getGrayImg(cv::Mat img) {
    cv::Mat grayImg;
    if(img.channels() ==4){
        cv::cvtColor(img,grayImg,cv::COLOR_BGRA2GRAY);
    }else if (img.channels() == 3) {
        cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    } else {
        grayImg = img;
    }

    return grayImg;
}


#endif // HEADER_H
