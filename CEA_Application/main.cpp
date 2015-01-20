/**
  * @file main.cpp
  * @brief Main of the application
  * @date December 2014
  * @author INSA
  */

#include "interface.h"
#include "document.h"
#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface w;
    w.show();

    return a.exec();
}
