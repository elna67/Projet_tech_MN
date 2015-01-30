/**
  * @class Document
  * @brief video processing and displaying
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <QMainWindow>
#include <QTime>
#include <QLCDNumber>
#include <QtGui>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <windows.h>
#include <QElapsedTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "view.h"
#include "interface.h"

//Include caltech
#include "LaneDetector.hh"
#include "cmdline.h"

#include <vector>
#include <string>
#include <fstream>

// Useful message macro
#define MSG(fmt, ...) \
    (fprintf(stdout, "%s:%d msg   " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__) ? 0 : 0)

// fin include caltech

using namespace std;
using namespace cv;
using namespace LaneDetector;

class Document
{
public:
    Document();

    friend class Interface;

private:
    View *view;
    cv::VideoCapture capVideo;
    Interface *inter;
    bool stop;

    QTimer* tmrTimer;
    QTime timer;
    cv::Mat matOriginal;
    QImage qimgOriginal;

    /* Options to select */
    bool isDisplayLanesSelected;

public:
    void startVideo(QString,QLabel*);
    QString openVideo();
    int process(int argc, char **argv, VideoCapture capVideo, QLabel *label);

};

#endif // DOCUMENT_H
