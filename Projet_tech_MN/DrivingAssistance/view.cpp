/**
  * @file view.cpp
  * @brief Implementation of the class View
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "view.h"
View::View()
{
    _dispRoad = 0;
    _dispTraj = 0;
}


/**
 * This function processes an input image and detects lanes/stoplines
 * based on the passed in command line arguments
 *
 * \param cameraInfo the camera calibration info
 * \param lanesConf the lane detection settings
 * \param stoplinesConf the stop line detection settings
 * \param options the command line arguments
 * \param outputFile the output file stream to write output lanes to
 * \param index the image index (used for saving output files)
 * \param elapsedTime if NOT NULL, it is accumulated with clock ticks for
 *        the detection operation
 */
/*void View::ProcessImage(CameraInfo& cameraInfo,
                        LaneDetectorConf& lanesConf, LaneDetectorConf& stoplinesConf,
                        gengetopt_args_info& options, ofstream* outputFile,
                        int index, clock_t *elapsedTime)*/
void View::ProcessImage(CameraInfo& cameraInfo,
                        LaneDetectorConf& lanesConf, clock_t *elapsedTime)
{
    // load the image
    CvMat *raw_mat, *mat;
    mcvLoadImage(_currentFrame, &raw_mat, &mat);

    // detect lanes

    _sceneFrame._lineScores.clear();
    _sceneFrame._splineScores.clear();
    _sceneFrame._lanes.clear();
    _sceneFrame._splines.clear();

    _carFrame._splinters.clear();


    clock_t startTime = clock();
    mcvGetLanes(mat, raw_mat, &(_sceneFrame._lanes), &(_sceneFrame._lineScores), &(_sceneFrame._splines), &(_sceneFrame._splineScores),
                &cameraInfo, &lanesConf, NULL);
    clock_t endTime = clock();

    //call function to get the principal lane MYRIAM
    if((_sceneFrame._splines).size()>=2){
        if(_dispRoad)
            _sceneFrame.principalWayAnalysis(mat,&(_carFrame._splinters),_dispTraj);
        if(_dispTraj)
            _carFrame.principalTrajectoryAnalysis();
    }

    // update elapsed time
    if (elapsedTime)
        (*elapsedTime) += endTime - startTime;



    // show detected lanes
    CvMat *imDisplay = cvCloneMat(raw_mat);
    int Rgb = 255*_dispTraj;
    int rGb = 255*_dispRoad;
    // print lanes

    if (lanesConf.ransacSpline)
    {
         if(_dispRoad || _dispTraj){

        for(int i=0+2*(int)(_dispTraj); i<(int)_carFrame._splinters.size(); i++)
        {
            // print numbers?
            //       if (options.show_lane_numbers_flag)
            {
                char str[256];
                //sprintf_s(str, "%d", i); //on linux :
                sprintf(str, "%d", i);

//                mcvDrawText(imDisplay, str,
//                            cvPointFrom32f(carFrame.splinters[i].points[carFrame.splinters[i].degree]),
//                        1, CV_RGB(0, 0, 255));
            }
            if ((_sceneFrame._splines)[i].color == LINE_COLOR_YELLOW)
                mcvDrawSpline(imDisplay, _carFrame._splinters[i], CV_RGB(Rgb,rGb,0), 3);
            else
            {
                mcvDrawSpline(imDisplay, _carFrame._splinters[i], CV_RGB(Rgb, rGb, 0), 3);
                _currentFrame = cvCloneMat(imDisplay);
            }
        }

         }

         else{
             cout<<" ";


             for(int i=0; i<(int)(_sceneFrame._splines).size(); i++)
             {
                 // print numbers?
                 //       if (options.show_lane_numbers_flag)
                 {
                     char str[256];
                     //sprintf_s(str, "%d", i); //on linux :
                     sprintf(str, "%d", i);

                     mcvDrawText(imDisplay, str,
                                 cvPointFrom32f((_sceneFrame._splines)[i].points[(_sceneFrame._splines)[i].degree]),
                             1, CV_RGB(0, 0, 255));
                 }
                 if ((_sceneFrame._splines)[i].color == LINE_COLOR_YELLOW)
                     mcvDrawSpline(imDisplay, (_sceneFrame._splines)[i], CV_RGB(Rgb,rGb,0), 3);
                 else
                 {
                     mcvDrawSpline(imDisplay, (_sceneFrame._splines)[i], CV_RGB(Rgb, rGb, 0), 3);
                     _currentFrame = cvCloneMat(imDisplay);
                 }
             }

         }
    }
    // clear
    cvReleaseMat(&imDisplay);
    cvReleaseMat(&raw_mat);
    cvReleaseMat(&mat);
}

