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
    ui->checkDisplayLane->setEnabled(false);

    doc = new Document();
    doc->inter = this;

    createActions();
    createMenus();

    ui->lblDisplayVideo->setAlignment(Qt::AlignCenter);

}


/**
 * @brief Interface::~Interface
 */
Interface::~Interface()
{
    delete ui;
}


/**
 * @brief Interface::createMenus
 * Initialize menu bar
 */
void Interface::createMenus()
{
    openMenu = menuBar()->addMenu(tr("&Open"));
    openMenu->addAction(openAct);
}


/**
 * @brief Interface::createActions
 * Initialize actions and connect slots
 */
void Interface::createActions()
{
    openAct = new QAction(tr("&Open video"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Select video to open"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openVideo()));

    connect(ui->checkDisplayLane, SIGNAL(clicked(bool)), this, SLOT(displayLane(bool)));
}


/**
 * @brief Interface::closeEvent
 * @param bar
 * Assure that the video process() is stopped before closing the application
 */
void Interface::closeEvent(QCloseEvent *bar)
{
    doc->stop = true;
}

/**
 * @brief Interface::on_btnStartOrStop_clicked
 * Start or stop the video
 */
void Interface::on_btnStartOrStop_clicked(){
    if(videoIsSelected){
        ui->checkDisplayLane->setEnabled(true);
        if(ui->btnStartOrStop->text() == "Start" || ui->btnStartOrStop->text() == "Restart")
        {
            openAct->setEnabled(false);
            openAct->setStatusTip(tr("Stop video first"));
            ui->btnStartOrStop->setText("Stop");
            doc->stop = false;

            tmrTimer = new QTimer(this);
            tmrTimer->start(20);

            doc->startVideo(filenameVideo,ui->lblDisplayVideo);
        }
        else
        {
            openAct->setEnabled(true);
            openAct->setStatusTip(tr("Select video to open"));
            ui->btnStartOrStop->setText("Restart");
            doc->stop = true;
            tmrTimer->stop();
        }
    }
    else ui->lblDisplayVideo->setText("Select a video to open first");
}



/**
 * @brief Interface::openVideo
 * Open a video to read
 */
void Interface::openVideo()
{
    doc->stop = false;
    filenameVideo = doc->openVideo();
    if(filenameVideo != NULL)
    {
        videoIsSelected = true;
        QFileInfo fi = filenameVideo;
        ui->lblDisplayVideo->setText("Video selected : " + fi.fileName());
    }
}


/**
 * @brief Interface::displayLane
 * Option to display the lanes
 */
void Interface::displayLane(bool checked){
    doc->isDisplayLanesSelected = checked;
}
