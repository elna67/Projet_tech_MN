#ifndef SCENE_H
#define SCENE_H

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

#include "mcv.hh"
#include "InversePerspectiveMapping.hh"
#include "LaneDetectorOpt.h"
#include "ranker.h"

#include "LaneConf.h"
#include "StopLinesConf.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <math.h>


#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace LaneDetector;

//#include "view.h"


class Scene
{
    friend class View;
protected:

    vector<FLOAT> _lineScores, _splineScores;
    vector<Line> _lanes;
    vector<Spline> _splines;


public:
    Scene();
    bool principalWayAnalysis(const CvMat *matimg, vector<Spline> *splinters,bool dispTraj);

};

#endif // SCENE_H

