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
#include "qfileinfo.h"

using namespace std;
using namespace cv;

namespace Ui {
class Interface;
}
class Document;
class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

    friend class Document;

private:
    Ui::Interface *ui;
    QMenu *openMenu;
    QAction *openAct;
    QAction *displayAct;

    QString filenameVideo;
    bool _videoIsSelected;

    cv::VideoCapture _capWebcam;

    Document* _doc;

private:
    void createActions();
    void createMenus();
    void closeEvent(QCloseEvent *bar);

private slots:
    void on_btnStartOrStop_clicked();
    void openVideo();
    void displayLane(bool);

    void displayMain(bool);
    void displayTraj(bool);
};

#endif // INTERFACE_H
