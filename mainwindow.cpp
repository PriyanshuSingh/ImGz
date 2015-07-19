#include <QMenu>
#include <QLabel>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QDockWidget>
#include <QLabel>
#include <QPalette>
#include "mainwindow.h"
#include "rasterlabel.h"
#include "circlefilter.h"
#include "openingfilter.h"
#include <iostream>
#include <QVBoxLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainImage = cv::imread("/home/abhishek/Desktop/openCV/Test/lena.jpg");

    //currentFilter = new CircleFilter();
    currentFilter=new OpeningFilter;
    rasterLabel = new RasterLabel(this);
    rasterLabel->setImage(mainImage);
    rasterLabel->setFilter(currentFilter);
    currentFilter->setImage(mainImage);
    rasterLabel->initRender();
    createMenu();
    createStatusBar();
    createDockWidget();
    createToolBar();
    createBottomDock();
    rasterLabel->setStyleSheet("background-color:black;");
    setCentralWidget(rasterLabel);

}

MainWindow::~MainWindow()
{

}


void MainWindow::createMenu()
{

}

void MainWindow::createStatusBar()
{

}

void MainWindow::createDockWidget()
{
    rightDock = new QDockWidget(QString("Properties"),this);
    //QVBoxLayout *rightDockLayout = new QVBoxLayout();
    //Qbutton *openingButton=new QButton;
    bottomDock = new QDockWidget(this);
    QWidget *j=new QWidget();
    j->setStyleSheet("background-color:red;");
    rightDock->setWidget(j);
    addDockWidget(Qt::RightDockWidgetArea,rightDock);
    addDockWidget(Qt::BottomDockWidgetArea,bottomDock);

}

void MainWindow::createToolBar()
{
    leftToolBar = new QToolBar(this);
    circleAction = new QAction(QString("Circle"),this);
    leftToolBar->addAction(circleAction);
    addToolBar(Qt::LeftToolBarArea, leftToolBar);
}

void MainWindow::createBottomDock(){
    currentFilter->updateBottomDock(bottomDock,this);
}
