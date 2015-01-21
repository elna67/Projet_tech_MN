/**
  * @file view.cpp
  * @brief Implementation of the class View
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "view.h"

View::View()
{
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
    vector<FLOAT> lineScores, splineScores;
    vector<Line> lanes;
    vector<Spline> splines;
    clock_t startTime = clock();
    mcvGetLanes(mat, raw_mat, &lanes, &lineScores, &splines, &splineScores,
                &cameraInfo, &lanesConf, NULL);
    clock_t endTime = clock();

    // update elapsed time
    if (elapsedTime)
        (*elapsedTime) += endTime - startTime;



    // show detected lanes
    CvMat *imDisplay = cvCloneMat(raw_mat);

    // print lanes
    if (lanesConf.ransacSpline)
    {
        for(int i=0; i<(int)splines.size(); i++)
        {
            // print numbers?
            //       if (options.show_lane_numbers_flag)
            {
                char str[256];
                sprintf_s(str, "%d", i);

                mcvDrawText(imDisplay, str,
                            cvPointFrom32f(splines[i].points[splines[i].degree]),
                        1, CV_RGB(0, 0, 255));
            }
            if (splines[i].color == LINE_COLOR_YELLOW)
                mcvDrawSpline(imDisplay, splines[i], CV_RGB(255,255,0), 3);
            else
            {
                mcvDrawSpline(imDisplay, splines[i], CV_RGB(0, 255, 0), 3);
                currentFrame = cvCloneMat(imDisplay);
            }
        }
    }
    // clear
    cvReleaseMat(&imDisplay);
    cvReleaseMat(&raw_mat);
    cvReleaseMat(&mat);
}
