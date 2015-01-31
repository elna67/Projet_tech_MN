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
    _videoIsSelected = false;
    ui->checkDisplayLane->setEnabled(false);

    _doc = new Document();
    _doc->_inter = this;

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
    connect(ui->checkMainRoad, SIGNAL(clicked(bool)), this, SLOT(displayMain(bool)));
    connect(ui->checkExpTraj, SIGNAL(clicked(bool)), this, SLOT(displayTraj(bool)));

}


/**
 * @brief Interface::closeEvent
 * @param bar
 * Assure that the video process() is stopped before closing the application
 */
void Interface::closeEvent(QCloseEvent *bar)
{
    _doc->_stop = true;
}

/**
 * @brief Interface::on_btnStartOrStop_clicked
 * Start or stop the video
 */
void Interface::on_btnStartOrStop_clicked(){
    if(_videoIsSelected){
        ui->checkDisplayLane->setEnabled(true);
        if(ui->btnStartOrStop->text() == "Start" || ui->btnStartOrStop->text() == "Restart")
        {
            openAct->setEnabled(false);
            openAct->setStatusTip(tr("Stop video first"));
            ui->btnStartOrStop->setText("Stop");
            _doc->_stop = false;

            _tmrTimer = new QTimer(this);
            _tmrTimer->start(20);

            _doc->startVideo(filenameVideo,ui->lblDisplayVideo);
        }
        else
        {
            openAct->setEnabled(true);
            openAct->setStatusTip(tr("Select video to open"));
            ui->btnStartOrStop->setText("Restart");
            _doc->_stop = true;
            _tmrTimer->stop();
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
    _doc->_stop = false;
    filenameVideo = _doc->openVideo();
    if(filenameVideo != NULL)
    {
        _videoIsSelected = true;
        QFileInfo fi = filenameVideo;
        ui->lblDisplayVideo->setText("Video selected : " + fi.fileName());
    }
}


/**
 * @brief Interface::displayLane
 * Option to display the lanes
 */
void Interface::displayLane(bool checked){

    _doc->_isDisplayLanesSelected = checked;
    ui->checkMainRoad->setEnabled(checked);

}

void Interface::displayMain(bool checked){
    _doc->_view->_dispRoad = checked;
    ui->checkExpTraj->setEnabled(checked);
    _doc->_view->_dispRoad = checked;
    ui->checkDisplayLane->setEnabled(!(ui->checkMainRoad->isChecked()));

}

void Interface::displayTraj(bool checked){
    _doc->_view->_dispTraj = checked;
    ui->checkMainRoad->setEnabled(!checked);
}

