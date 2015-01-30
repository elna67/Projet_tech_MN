/**
  * @file view.cpp
  * @brief Implementation of the class View
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "view.h"
#include "myadditionals.h"
View::View()
{
    dispRoad = 0;
    dispTraj = 0;
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
    mcvLoadImage(currentFrame, &raw_mat, &mat);

    // detect lanes

    sceneFrame.lineScores.clear();
    sceneFrame.splineScores.clear();
    sceneFrame.lanes.clear();
    sceneFrame.splines.clear();

    carFrame.splinters.clear();


    clock_t startTime = clock();
    mcvGetLanes(mat, raw_mat, &(sceneFrame.lanes), &(sceneFrame.lineScores), &(sceneFrame.splines), &(sceneFrame.splineScores),
                &cameraInfo, &lanesConf, NULL);
    clock_t endTime = clock();

    //call function to get the principal lane MYRIAM
    if((sceneFrame.splines).size()>=2){
        if(dispRoad)
            sceneFrame.principalWayAnalysis(mat,&(carFrame.splinters),dispTraj);
        if(dispTraj)
            carFrame.principalTrajectoryAnalysis();
    }

    // update elapsed time
    if (elapsedTime)
        (*elapsedTime) += endTime - startTime;



    // show detected lanes
    CvMat *imDisplay = cvCloneMat(raw_mat);
    int Rgb = 255*dispTraj;
    int rGb = 255*dispRoad;
    // print lanes

    if (lanesConf.ransacSpline)
    {
         if(dispRoad || dispTraj){

        for(int i=0+2*(int)(dispTraj); i<(int)carFrame.splinters.size(); i++)
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
            if ((sceneFrame.splines)[i].color == LINE_COLOR_YELLOW)
                mcvDrawSpline(imDisplay, carFrame.splinters[i], CV_RGB(Rgb,rGb,0), 3);
            else
            {
                mcvDrawSpline(imDisplay, carFrame.splinters[i], CV_RGB(Rgb, rGb, 0), 3);
                currentFrame = cvCloneMat(imDisplay);
            }
        }

         }

         else{
             cout<<" ";


             for(int i=0; i<(int)(sceneFrame.splines).size(); i++)
             {
                 // print numbers?
                 //       if (options.show_lane_numbers_flag)
                 {
                     char str[256];
                     //sprintf_s(str, "%d", i); //on linux :
                     sprintf(str, "%d", i);

                     mcvDrawText(imDisplay, str,
                                 cvPointFrom32f((sceneFrame.splines)[i].points[(sceneFrame.splines)[i].degree]),
                             1, CV_RGB(0, 0, 255));
                 }
                 if ((sceneFrame.splines)[i].color == LINE_COLOR_YELLOW)
                     mcvDrawSpline(imDisplay, (sceneFrame.splines)[i], CV_RGB(Rgb,rGb,0), 3);
                 else
                 {
                     mcvDrawSpline(imDisplay, (sceneFrame.splines)[i], CV_RGB(Rgb, rGb, 0), 3);
                     currentFrame = cvCloneMat(imDisplay);
                 }
             }

         }
    }
    // clear
    cvReleaseMat(&imDisplay);
    cvReleaseMat(&raw_mat);
    cvReleaseMat(&mat);
}
