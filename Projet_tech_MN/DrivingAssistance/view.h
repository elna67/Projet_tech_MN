/**
  * @class View
  * @brief image processing
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <QElapsedTimer>

/* caltech */
#include "LaneDetector.hh"

// Useful message macro
#define MSG(fmt, ...) \
    (fprintf(stdout, "%s:%d msg   " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__) ? 0 : 0)
/* end caltech */

using namespace std;
using namespace cv;
using namespace LaneDetector;

#include "scene.h"
#include "car.h"
class View
{
    friend class Scene;
    friend class Document;
public:
    View();

    /*void ProcessImage(CameraInfo& cameraInfo,
                                LaneDetectorConf& lanesConf, LaneDetectorConf& stoplinesConf,
                                gengetopt_args_info& options, ofstream* outputFile,
                                int index, clock_t *elapsedTime);*/
    void ProcessImage(CameraInfo& cameraInfo,
                            LaneDetectorConf& lanesConf, clock_t *elapsedTime);
    bool _dispRoad;
    bool _dispTraj;

private:
    Mat _currentFrame;

    Scene _sceneFrame;
    Car _carFrame;

};

#endif // VIEW_H

