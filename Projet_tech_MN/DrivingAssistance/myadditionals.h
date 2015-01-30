#ifndef MYADDITIONALS_H
#define MYADDITIONALS_H

//class MyAdditionals
//{
//public:
//    MyAdditionals();
//};


#include <vector>
#include <string>
#include "LaneDetector.hh"
#include "cmdline.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "LaneDetector.hh"

#include "mcv.hh"
#include "InversePerspectiveMapping.hh"
#include "LaneDetectorOpt.h"
#include "ranker.h"

#include "LaneConf.h"
#include "StopLinesConf.h"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>


#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace LaneDetector;

bool principalWayAnalysis(const CvMat *matimg, vector<Line> *lanes,
                          vector<FLOAT>*lineScores,
                          vector<Spline> *splines, vector<FLOAT> *splineScores,
                          vector<Spline> *splinters);


Spline principalTrajectoryAnalysis(const CvMat *matimg, vector<Line> *lanes,
                                 vector<FLOAT>*lineScores,
                                 vector<Spline> *splines, vector<FLOAT> *splineScores,
                                 vector<Spline> *splinters);

Line getLineWay(vector<Spline> *splines);
bool principalTrajectoryAnalysis(vector<Spline> *splinters);

#endif // MYADDITIONALS_H
