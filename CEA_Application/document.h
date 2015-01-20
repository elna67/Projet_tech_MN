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


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "view.h"
#include "interface.h"

//Include caltech
#include "mcv.hh"
#include "InversePerspectiveMapping.hh"
#include "LaneDetector.hh"
#include "cmdline.h"

#include <vector>
#include <string>
// fin include caltech

using namespace std;
using namespace cv;
using namespace LaneDetector;

class Document
{
public:
    Document();

    friend class View;
    friend class Interface;

private:
    View *view;
    cv::VideoCapture capVideo;
    Interface *inter;
    bool stop;

    /* Options to select */
    bool isDisplayLanesSelected;

    QTimer* tmrTimer;
    QTime timer;
    cv::Mat matOriginal;
    QImage qimgOriginal;

    void startVideo(QString,QLabel*);
    QString openVideo();


    int process(int argc, char **argv, VideoCapture capVideo, QLabel *label);

    void ProcessImage(CvMat matInit, CameraInfo& cameraInfo,
                      LaneDetectorConf& lanesConf, LaneDetectorConf& stoplinesConf,
                      gengetopt_args_info& options, ofstream* outputFile,
                      int index, clock_t *elapsedTime);


private slots:
    void processFrameAndUpdateGUI(VideoCapture,QLabel*);
};

#endif // DOCUMENT_H
