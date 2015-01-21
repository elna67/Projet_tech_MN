#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T15:06:12
#
#-------------------------------------------------

QT       += core gui\
            widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CEA_Application
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        interface.cpp \
    document.cpp \
    view.cpp \
    InversePerspectiveMapping.cc \
    LaneDetector.cc \
    mcv.cc \
    CameraInfoOpt.c \
    cmdline.c \
    LaneDetectorOpt.c

HEADERS  += interface.h \
    document.h \
    view.h \
    CameraInfo.h \
    CameraInfoOpt.h \
    cmdline.h \
    LaneConf.h \
    LaneDetectorOpt.h \
    ranker.h \
    StopLinesConf.h \
    InversePerspectiveMapping.hh \
    LaneDetector.hh \
    mcv.hh

FORMS    += interface.ui

INCLUDEPATH += C:\\OpenCV2.3.1\\opencv\\build\\include

LIBS += -LC:\\OpenCV2.3.1\\build\\lib\\Debug \
    -lopencv_calib3d231d \
    -lopencv_contrib231d \
    -lopencv_core231d \
    -lopencv_features2d231d \
    -lopencv_flann231d \
    -lopencv_gpu231d \
    -lopencv_highgui231d \
    -lopencv_imgproc231d \
    -lopencv_legacy231d \
    -lopencv_ml231d \
    -lopencv_objdetect231d \
    -lopencv_ts231d \
    -lopencv_video231d

OTHER_FILES += \
    CameraInfo.conf \
    Lanes.conf \
    Lanes-mode2.conf \
    Stoplines.conf
