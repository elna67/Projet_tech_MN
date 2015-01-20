/**
  * @class View
  * @brief image processing
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <QMainWindow>
#include <QTime>
#include <QLCDNumber>
#include <QtGui>

#include "interface.h"
#include "document.h"

using namespace std;
using namespace cv;

class View
{
public:
    friend class Document;
    View();

    void displayLanes(bool);

private:
    Mat currentFrame;
};

#endif // VIEW_H
