#ifndef CAR_H
#define CAR_H

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


class Car
{
    friend class View;
protected:
    vector<Spline> _splinters;
public:
    Car();

    void principalTrajectoryAnalysis();


};

#endif // CAR_H

