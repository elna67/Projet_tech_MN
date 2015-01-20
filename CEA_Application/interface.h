/**
  * @class Interface
  * @brief Interface of the application
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QTime>
#include <QLCDNumber>
#include <QtGui>
#include <QString>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "document.h"
#include "view.h"

using namespace std;
using namespace cv;

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

    friend class Document;

private:
    Ui::Interface *ui;

    QString filenameVideo;
    bool videoIsSelected;

    QTimer* tmrTimer;
    QTime timer;
    cv::VideoCapture capWebcam;
    //cv::Mat matOriginal;
    //QImage qimgOriginal;

    Document* doc;

private slots:
    void on_btnPauseOrResume_clicked();
    void on_btnStartOrStop_clicked();
    void on_btnDisplayLane_clicked();
    void on_btnOpenVideo_clicked();

};

#endif // INTERFACE_H
