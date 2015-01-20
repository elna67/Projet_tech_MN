/**
  * @file interface.cpp
  * @brief Implementation of the class Interface
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "interface.h"
#include "ui_interface.h"


/**
 * @brief Interface::Interface
 * @param parent
 */
Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    videoIsSelected = false;
    ui->btnPauseOrResume->setEnabled(false);

    doc = new Document();
    doc->inter = this;

    //doc->process(NULL, NULL);
}


/**
 * @brief Interface::~Interface
 */
Interface::~Interface()
{
    delete ui;
}


/**
 * @brief Interface::on_btnPauseOrResume_clicked
 * Pause or resume the video (this function is not used yet)
 */
void Interface::on_btnPauseOrResume_clicked()
{
    // not used yet, is this button really necessary ?
    if(ui->btnPauseOrResume->text() == "Pause") ui->btnPauseOrResume->setText("Resume");
    else ui->btnPauseOrResume->setText("Pause");
}


/**
 * @brief Interface::on_btnStartOrStop_clicked
 * Start or stop the video
 */
void Interface::on_btnStartOrStop_clicked(){
    if(videoIsSelected){
        if(ui->btnStartOrStop->text() == "Start" || ui->btnStartOrStop->text() == "Restart")
        {
            ui->btnOpenVideo->setEnabled(false);
            ui->btnStartOrStop->setText("Stop");
            doc->stop = false;

            tmrTimer = new QTimer(this);
            tmrTimer->start(20);

            doc->startVideo(filenameVideo,ui->lblDisplayVideo);
        }
        else
        {
            ui->btnOpenVideo->setEnabled(true);
            ui->btnStartOrStop->setText("Restart");
            doc->stop = true;
            tmrTimer->stop();
        }
    }
    else ui->lblDisplayVideo->setText("Select a video to open first");
}


/**
 * @brief Interface::on_btnOpenVideo_clicked
 * Open a video to read
 */
void Interface::on_btnOpenVideo_clicked(){
    doc->stop = false;
    filenameVideo = doc->openVideo();
    if(filenameVideo != NULL)
    {
        videoIsSelected = true;
        ui->lblDisplayVideo->setText("Video selected : " + filenameVideo);
    }
}



/**
 * @brief Interface::on_btnDisplayLane_clicked
 * Option to display the lanes
 */
void Interface::on_btnDisplayLane_clicked(){
    if(!doc->isDisplayLanesSelected)
    {
        doc->isDisplayLanesSelected = true;
        ui->btnDisplayLane->setText("Stop display lane");
    }
    else
    {
        doc->isDisplayLanesSelected = false;
        ui->btnDisplayLane->setText("Display lane");
    }
}
