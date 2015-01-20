/**
  * @file document.cpp
  * @brief Implementation of the class Document
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "document.h"

//Include et define caltech
#include "cmdline.h"
#include "LaneDetector.hh"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

#include <opencv/cv.h>
#include <opencv/highgui.h>

// Useful message macro
#define MSG(fmt, ...) \
    (fprintf(stdout, "%s:%d msg   " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__) ? 0 : 0)

// Useful error macro
#define ERROR(fmt, ...) \
    (fprintf(stderr, "%s:%d error " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__) ? -1 : -1)

//Fin include et define caltech


/**
 * @brief Document::Document
 */
Document::Document()
{
    cout << "new Doc" << endl;
    view = new View();
    stop = false;

    isDisplayLanesSelected = false;
}


/**
 * @brief Document::openVideo
 * Choice of the video to open
 * @return the name of the video file selected
 */
QString Document::openVideo()
{
    QWidget* videoDlg = new QWidget();
    QString filename = QFileDialog::getOpenFileName(videoDlg,"Select video to open","Video","Videos (*.avi *.mpeg *.mp4)"); // which video formats necessary ?

    return filename;
}


/**
 * @brief Document::startVideo
 * @param filename the video file to read
 * @param label
 * Start the video from the file selected
 */
void Document::startVideo(QString filename,QLabel* label)
{
    capVideo.open(filename.toStdString());

    if(!capVideo.isOpened())return; //check if succeed

    //processFrameAndUpdateGUI(capVideo,label);
    process(NULL,NULL,capVideo,label);

}

/**
 * @brief Document::processFrameAndUpdateGUI
 * @param capVideo
 * @param label
 * Display the video frame by frame in the interface
 */
void Document::processFrameAndUpdateGUI(VideoCapture capVideo,QLabel* label){
    int fps = capVideo.get(CV_CAP_PROP_FPS);
    int cpt = 0;
    while(!stop)
    {
        capVideo.read(view->currentFrame);
        cout << "Process call : " << cpt << endl;
        cpt++;

        //if(isDisplayLanesSelected) process(NULL,NULL);


        /* Call of the options */
        //view->displayLanes(isDisplayLanesSelected);

        QImage qimgOriginal((uchar*)view->currentFrame.data, view->currentFrame.cols, view->currentFrame.rows, view->currentFrame.step, QImage::Format_RGB888);


        label->setPixmap(QPixmap::fromImage(qimgOriginal));

        Sleep(1000/fps);

        qApp->processEvents();
    }
}


/**
 * @brief Document::process
 * Video processing depending on the selected options
 */
int Document::process(int argc, char** argv,VideoCapture capVideo,QLabel* label)
{
    // parse the command line paramters
    gengetopt_args_info options;
    if (cmdline_parser (argc, argv,  &options) < 0)
        return -1;

    // read the cameracordova2 configurations
    CameraInfo cameraInfo;
    mcvInitCameraInfo(options.camera_conf_arg, &cameraInfo);
    MSG("Loaded camera file");

    // read the configurations
    LaneDetectorConf lanesConf, stoplinesConf;
    if (!options.no_lanes_flag)
    {
        mcvInitLaneDetectorConf(options.lanes_conf_arg, &lanesConf);
        MSG("Loaded lanes config file");
    }
    if (!options.no_stoplines_flag)
    {
        mcvInitLaneDetectorConf2(options.stoplines_conf_arg, &stoplinesConf);
        MSG("Loaded stop lines config file");
    }


    //Starting reading of the video
    int fps = capVideo.get(CV_CAP_PROP_FPS);
    int cpt = 0;
    while(!stop)
    {
        capVideo.read(view->currentFrame);
        cout << "Process call : " << cpt << endl;
        cpt++;
        CvMat matInit = view->currentFrame;

        if(isDisplayLanesSelected){

            // set debug to true
            if (options.debug_flag)
                DEBUG_LINES = 1;

            // process a single image
            if (options.image_file_given)
            {
                // elapsed time
                clock_t elapsed = 0;
                /*    ProcessImage(options.image_file_arg, cameraInfo, lanesConf, stoplinesConf,
                    options, NULL, elapsed, 0);*/
                ProcessImage(matInit, cameraInfo, lanesConf, stoplinesConf,
                             options, NULL, elapsed, 0);
                double elapsedTime = static_cast<double>(elapsed) / CLOCKS_PER_SEC;
                /*MSG("Total time %f secs for 1 image = %f Hz", elapsedTime,
          1. / elapsedTime);*/
            }

            // process a list of images
            //   if (options.list_file_given)
            {
                // get the path if exists
                string path = "";
                if (options.list_path_given)
                    path = options.list_path_arg;

                // read file
                vector<string> files;
                //    ReadLines(options.list_file_arg, &files);
                int numImages = files.size();

                if (numImages<1)
                    ERROR("File %s is empty", options.list_file_arg);
                //    else
                {
                    // save results?
                    ofstream outputFile;
                    stringstream ss;
                    if (options.save_lanes_flag)
                    {
                        ss << options.list_file_arg << options.output_suffix_arg << ".txt";
                        outputFile.open(ss.str().c_str(), ios_base::out);
                    }

                    // elapsed time
                    clock_t elapsed = 0;
                    // loop
                    //      for (int i=0; i<numImages; ++i)
                    /*for (int i = 119; i < 249;i++)
        {
            string a = "caltech-lanes/cordova1/f00";
            string b = std::to_string((long double)i);
            string c = ".png";
            string d = a + b + c;
            const char* name = d.c_str();
  //        string imageFile = path + files[i];
  //        MSG("Processing image: %s", imageFile.c_str());*/
                    /*        ProcesfilenamesImage(imageFile.c_str(), cameraInfo, lanesConf, stoplinesConf,
                       options, &outputFile, i, &elapsed);*/
                    ProcessImage(matInit, cameraInfo, lanesConf, stoplinesConf,
                                 options, NULL, 0, &elapsed);
                    //}
                    double elapsedTime = static_cast<double>(elapsed) / CLOCKS_PER_SEC;
                    /*MSG("Total time %f secs for %d images = %f Hz",
            elapsedTime, numImages, numImages / elapsedTime);*/

                    // close results file (if open)
                    /*if (options.save_lanes_flag)
        {
          outputFile.close();
          MSG("Results written to %s", ss.str().c_str());
        }*/
                }
            }
        }

        QImage qimgOriginal((uchar*)view->currentFrame.data, view->currentFrame.cols, view->currentFrame.rows, view->currentFrame.step, QImage::Format_RGB888);


        label->setPixmap(QPixmap::fromImage(qimgOriginal));

        Sleep(1000/fps);

        qApp->processEvents();
    }
    return 0;
}

/**
 * This function processes an input image and detects lanes/stoplines
 * based on the passed in command line arguments
 *
 * \param filename the input file name
 * \param cameraInfo the camera calibration info
 * \param lanesConf the lane detection settings
 * \param stoplinesConf the stop line detection settings
 * \param options the command line arguments
 * \param outputFile the output file stream to write output lanes to
 * \param index the image index (used for saving output files)
 * \param elapsedTime if NOT NULL, it is accumulated with clock ticks for
 *        the detection operation
 */
void Document::ProcessImage(CvMat matInit, CameraInfo& cameraInfo,
                            LaneDetectorConf& lanesConf, LaneDetectorConf& stoplinesConf,
                            gengetopt_args_info& options, ofstream* outputFile,
                            int index, clock_t *elapsedTime)
{

    // load the image
    CvMat *raw_mat, *mat;
    mcvLoadImage(matInit, &raw_mat, &mat);

    // detect lanes
    vector<FLOAT> lineScores, splineScores;
    vector<Line> lanes;
    vector<Spline> splines;
    clock_t startTime = clock();
    mcvGetLanes(mat, raw_mat, &lanes, &lineScores, &splines, &splineScores,
                &cameraInfo, &lanesConf, NULL);
    clock_t endTime = clock();
    /*MSG("Found %d lanes in %f msec", splines.size(),
      static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000.);*/
    // update elapsed time
    if (elapsedTime)
        (*elapsedTime) += endTime - startTime;

    // save results?
    if (options.save_lanes_flag && outputFile && outputFile->is_open())
    {
        (*outputFile) << "frame#" << setw(8) << setfill('0') << index <<
                         " has " << splines.size() << " splines" << endl;
        for (int i=0; i<splines.size(); ++i)
        {
            (*outputFile) << "\tspline#" << i+1 << " has " <<
                             splines[i].degree+1 << " points and score " <<
                             splineScores[i] << endl;
            for (int j=0; j<=splines[i].degree; ++j)
                (*outputFile) << "\t\t" <<
                                 splines[i].points[j].x << ", " <<
                                 splines[i].points[j].y << endl;
        }
    }

    // show or save
    //  if (options.show_flag || options.save_images_flag)
    {
        // show detected lanes
        CvMat *imDisplay = cvCloneMat(raw_mat);


        // convert to BGR
        //     cvCvtColor(raw_mat, imDisplay, CV_RGB2BGR);



        // print lanes
        if (lanesConf.ransacSpline)
        {
            for(int i=0; i<splines.size(); i++)
            {
                // print numbers?
                //       if (options.show_lane_numbers_flag)
                {
                    char str[256];
                    sprintf(str, "%d", i);
                    mcvDrawText(imDisplay, str,
                                cvPointFrom32f(splines[i].points[splines[i].degree]),
                            1, CV_RGB(0, 0, 255));
                }
                if (splines[i].color == LINE_COLOR_YELLOW)
                    mcvDrawSpline(imDisplay, splines[i], CV_RGB(255,255,0), 3);
                else
                {
                    mcvDrawSpline(imDisplay, splines[i], CV_RGB(0, 255, 0), 3);
                    //SHOW_IMAGE(imDisplay, "Detected Lanes", 30); //Comment Elaine
                    view->currentFrame = cvCloneMat(imDisplay);

                }


            }
        }
        // show?
        if (options.show_flag)
        {
            // set the wait value
            int wait = options.step_flag ? 0 : options.wait_arg;
            // show image with detected lanes
            //SHOW_IMAGE(imDisplay, "Detected Lanes", wait); //Comment Elaine
        }
        // save?
        /*if (options.save_images_flag)
    {
      // file name
      stringstream ss;
      ss << filename << options.output_suffix_arg << "_" << setw(6) <<
        setfill('0') << index << ".png";
      string outFilename = ss.str();
      // save the image file
      MSG("Writing output image: %s", outFilename.c_str());
      cvSaveImage(outFilename.c_str(), imDisplay);
    }*/
        // clear
        cvReleaseMat(&imDisplay);
    }

    cvReleaseMat(&raw_mat);
    cvReleaseMat(&mat);
}
