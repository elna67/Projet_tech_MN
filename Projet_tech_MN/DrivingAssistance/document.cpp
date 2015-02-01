/**
  * @file document.cpp
  * @brief Implementation of the class Document
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "document.h"


/**
 * @brief Document::Document
 */
Document::Document()
{
    _view = new View();
    _stop = false;

    _isDisplayLanesSelected = false;
}


/**
 * @brief Document::openVideo
 * Choice of the video to open
 * @return the name of the video file selected
 */
QString Document::openVideo()
{
    QWidget* videoDlg = new QWidget();
    QString filename = QFileDialog::getOpenFileName(videoDlg,"Select video to open",NULL,"Videos (*.avi *.mpeg *.mp4)"); // which video formats necessary ?

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
    _capVideo.open(filename.toStdString());

    if(!_capVideo.isOpened())return; //check if succeed

    //processFrameAndUpdateGUI(capVideo,label);
    process(NULL,NULL,_capVideo,label);

}


/**
 * @brief Document::process
 * @param argc
 * @param argv
 * @param capVideo
 * @param label
 * @return
 * Video processing depending on the selected options
 */
int Document::process(int argc, char** argv,VideoCapture capVideo,QLabel* label)
{
    // Timer
    QElapsedTimer timer;


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
    //cout << "mon beau fps : " << fps << endl;
    while(!_stop)
    {
        timer.start();
        capVideo.read(_view->_currentFrame);

        if(_isDisplayLanesSelected){

            // set debug to true
            if (options.debug_flag)
                DEBUG_LINES = 1;

            // process a single image
            if (options.image_file_given)
            {
                // elapsed time
                clock_t elapsed = 0;

                /*view->ProcessImage(cameraInfo, lanesConf, stoplinesConf,
                                   options, NULL, 0, &elapsed);*/
                _view->ProcessImage(cameraInfo, lanesConf, &elapsed);

                cout << "processImage is called" << endl;
            }

            //Timer end
            int tElapsed = timer.elapsed();
            cout << "process() execution : " << tElapsed << "milliseconds" << endl;

            // get the path if exists
            string path = "";
            if (options.list_path_given)
                path = options.list_path_arg;

            // read file
            vector<string> files;
            //    ReadLines(options.list_file_arg, &files);
            int numImages = files.size();

            if (numImages<1)
                //cout<< "file"<<options.list_file_arg<<" is empty "<<endl; //000file is emptyERROR("File %s is empty", options.list_file_arg);
                cout << "file is emtpy" << endl;
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

            /*view->ProcessImage(cameraInfo, lanesConf, stoplinesConf,
                               options, NULL, 0, &elapsed);*/
            _view->ProcessImage(cameraInfo, lanesConf, &elapsed);

        }

        /* Display video on the interface */

        // convert to BGR
        Mat imDisplay = _view->_currentFrame.clone();
        cvtColor(_view->_currentFrame, imDisplay,CV_BGR2RGB);

        QImage qimgOriginal((uchar*)imDisplay.data, imDisplay.cols,
                            imDisplay.rows, imDisplay.step, QImage::Format_RGB888);

        label->setPixmap(QPixmap::fromImage(qimgOriginal));
        //FCT_SLEEP;

#ifdef __gnu_linux__
                std::this_thread::sleep_for(std::chrono::milliseconds((const int)(1000/floor(20+1))));
#endif

#ifdef _WIN32
        Sleep(1000/fps);
#endif
        qApp->processEvents();
    }
    return 0;
}

