#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T15:37:47
#
#-------------------------------------------------

QT       += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImGz
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    rasterlabel.cpp \
    filter.cpp \
    circlefilter.cpp \
    openingfilter.cpp

INCLUDEPATH += /usr/local/include/Opencv

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videoio -lopencv_videostab

HEADERS  += \
    mainwindow.h \
    rasterlabel.h \
    filter.h \
    circlefilter.h \
    openingfilter.h

FORMS    +=
