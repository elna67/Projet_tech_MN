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

#ifdef _WIN32
#include <windows.h>
//#define FCT_SLEEP Sleep(1000/fps)
#endif

#ifdef __gnu_linux__
#define FCT_SLEEP std::this_thread::sleep_for(std::chrono::milliseconds((const int)(1000/floor(20+1))))
#include <chrono>
#include <thread>
#include <unistd.h>
#endif

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
#include <QElapsedTimer>

// Useful message macro
#define MSG(fmt, ...) \
    (fprintf(stdout, "%s:%d msg   " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__) ? 0 : 0)

// fin include caltech

using namespace std;
using namespace cv;
using namespace LaneDetector;


class Interface;
class Document
{
public:
    Document();

    friend class Interface;

private:
    View *_view;
    cv::VideoCapture _capVideo;
    Interface *_inter;
    bool _stop;

//    QTimer* _tmrTimer;
//    QTime _timer;
//    cv::Mat _matOriginal;
//    QImage _qimgOriginal;

    /* Options to select */
    bool _isDisplayLanesSelected;

public:
    void startVideo(QString,QLabel*);
    QString openVideo();
    int process(int argc, char **argv, VideoCapture _capVideo, QLabel *label);

};

#endif // DOCUMENT_H

