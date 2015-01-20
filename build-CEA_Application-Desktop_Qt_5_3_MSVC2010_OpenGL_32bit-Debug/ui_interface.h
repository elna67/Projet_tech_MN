/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QAction *actionVideo;
    QWidget *centralWidget;
    QPushButton *btnPauseOrResume;
    QPushButton *btnStartOrStop;
    QPushButton *btnDisplayLane;
    QLabel *lblDisplayVideo;
    QPushButton *btnOpenVideo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QStringLiteral("Interface"));
        Interface->resize(798, 600);
        actionVideo = new QAction(Interface);
        actionVideo->setObjectName(QStringLiteral("actionVideo"));
        centralWidget = new QWidget(Interface);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnPauseOrResume = new QPushButton(centralWidget);
        btnPauseOrResume->setObjectName(QStringLiteral("btnPauseOrResume"));
        btnPauseOrResume->setGeometry(QRect(190, 500, 75, 23));
        btnStartOrStop = new QPushButton(centralWidget);
        btnStartOrStop->setObjectName(QStringLiteral("btnStartOrStop"));
        btnStartOrStop->setGeometry(QRect(190, 470, 75, 23));
        btnDisplayLane = new QPushButton(centralWidget);
        btnDisplayLane->setObjectName(QStringLiteral("btnDisplayLane"));
        btnDisplayLane->setGeometry(QRect(290, 470, 131, 23));
        lblDisplayVideo = new QLabel(centralWidget);
        lblDisplayVideo->setObjectName(QStringLiteral("lblDisplayVideo"));
        lblDisplayVideo->setGeometry(QRect(30, 10, 731, 421));
        btnOpenVideo = new QPushButton(centralWidget);
        btnOpenVideo->setObjectName(QStringLiteral("btnOpenVideo"));
        btnOpenVideo->setGeometry(QRect(90, 470, 75, 23));
        Interface->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Interface);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 798, 21));
        Interface->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Interface);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Interface->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Interface);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Interface->setStatusBar(statusBar);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "Interface", 0));
        actionVideo->setText(QApplication::translate("Interface", "Video", 0));
        btnPauseOrResume->setText(QApplication::translate("Interface", "Pause", 0));
        btnStartOrStop->setText(QApplication::translate("Interface", "Start", 0));
        btnDisplayLane->setText(QApplication::translate("Interface", "Display Lane", 0));
        lblDisplayVideo->setText(QApplication::translate("Interface", "Video", 0));
        btnOpenVideo->setText(QApplication::translate("Interface", "Open Video", 0));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
