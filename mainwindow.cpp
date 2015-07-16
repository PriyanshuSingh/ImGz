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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ii = cv::imread("/home/priyanshu/Projects/ImGz/lena.bmp");

    ceff = new CircleFilter();
    rasterLabel = new RasterLabel(this);
    rasterLabel->setImage(ii);
    rasterLabel->setFilter(ceff);
    ceff->setImage(ii);
    rasterLabel->initRender();
    createMenu();
    createStatusBar();
    createDockWidget();
    createToolBar();
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
    bottomDock = new QDockWidget(this);
    //rightDock->setStyleSheet("background-color:red;");
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
