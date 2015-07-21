#include <QMenu>
#include <QLabel>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QDockWidget>
#include <QLabel>
#include <QPalette>
#include <QFileDialog>
#include "mainwindow.h"
#include "rasterlabel.h"
#include "circlefilter.h"
#include "morphOperations.h"
#include "dotpatternfilter.h"
#include <iostream>
#include <QVBoxLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //mainImage = cv::imread("/Users/tgz/Documents/cvTutorial/opencvTutorial/opencvTutorial/lena.jpg");

    rasterLabel = new RasterLabel(this);
    logTxtEdit = new QPlainTextEdit(this);
    logTxtEdit->setReadOnly(true);
    createFilter();
    createAction();
    createMenu();
    createStatusBar();
    createDockWidget();
    createToolBar();

    setCentralWidget(rasterLabel);
    connect(rasterLabel,SIGNAL(mouseMoved(QMouseEvent*)),this,SLOT(updateStatusBar(QMouseEvent*)));

}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{

    filePath = QFileDialog::getOpenFileName(this,QString("Open Image"),QString("."));
    if(!filePath.isEmpty()){
        // TODO
        std::string a = filePath.toUtf8().constData();
        mainImage = cv::imread(a);
        rasterLabel->setImage(mainImage);
    }
}

void MainWindow::updateStatusBar(QMouseEvent *ev)
{
    xyLabel->setText(QString("x:")+QString::number(ev->pos().x())+QString("|y:")+QString::number(ev->pos().y()));
}

void MainWindow::enableCircleFilter()
{
    currentFilter = circleFitler;
    rasterLabel->setFilter(currentFilter);
    logTxtEdit->appendPlainText(QString("Circle Filter selected"));
    updateDock();
}

void MainWindow::enableMorphFilter()
{
    currentFilter = morphFilter;
    rasterLabel->setFilter(currentFilter);
    logTxtEdit->appendPlainText(QString("Morph Filter selected"));
    updateDock();
}

void MainWindow::enableRectangleFilter()
{
    currentFilter = rectangleFilter;
    rasterLabel->setFilter(currentFilter);
    logTxtEdit->appendPlainText(QString("Rectangle Filter selected"));
    updateDock();
}

void MainWindow::enableWebcam()
{
    rasterLabel->setImageFromWebcam(true);
    logTxtEdit->appendPlainText(QString("Webcam Enabled"));
    setFixedSize(sizeHint());
}

void MainWindow::enableCircleDetectorFilter()
{
    currentFilter = circleDetectorFilter;
    rasterLabel->setFilter(currentFilter);
    logTxtEdit->appendPlainText(QString("Circle Detector selected"));
    updateDock();
}

void MainWindow::enableDotPatternFilter()
{
    currentFilter = dotPatternFilter;
    rasterLabel->setFilter(currentFilter);
    logTxtEdit->appendPlainText(QString("Dot pattern selected"));
}


void MainWindow::createAction()
{
    // filters and effects //

    // circleAction defination
    circleAction = new QAction(QString("Circle"),this);
    circleAction->setStatusTip(QString("Draws the circle on the image"));
    connect(circleAction,SIGNAL(triggered(bool)),this,SLOT(enableCircleFilter()));

    // morphAction defination
    morphAction = new QAction(QString("Morph"),this);
    morphAction->setStatusTip(QString("Morph effect"));
    connect(morphAction,SIGNAL(triggered(bool)),this,SLOT(enableMorphFilter()));

    // rectangleAction defination
    rectangleAction = new QAction(QString("Rectangle"),this);
    rectangleAction->setStatusTip(QString("Draws the rectangle on the image"));
    connect(rectangleAction,SIGNAL(triggered(bool)),this,SLOT(enableRectangleFilter()));

    // circleDetectorAction defination
    circleDetectorAction = new QAction(QString("Circle Detector"),this);
    circleDetectorAction->setStatusTip(QString("Detect circles in the image"));
    connect(circleDetectorAction,SIGNAL(triggered(bool)),this,SLOT(enableCircleDetectorFilter()));

    // dotPatternAction defination
    dotPatternAction = new QAction(QString("Dot Pattern"),this);
    connect(dotPatternAction,SIGNAL(triggered(bool)),this,SLOT(enableDotPatternFilter()));


    // Menu Action //

    // openAction defination
    openAction = new QAction(QString("&Open"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(QString("Open an image file"));
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

    //openWebcamAction defination
    openWebcamAction = new QAction(QString("webcam"),this);
    connect(openWebcamAction,SIGNAL(triggered(bool)),this,SLOT(enableWebcam()));

    // saveAction defination
    saveAction = new QAction(QString("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(QString("save an image file"));

    // aboutAction defination
    aboutAction = new QAction(QString("About"),this);
    aboutAction->setStatusTip(QString("About this project"));
}


void MainWindow::createMenu()
{
    // file Menu
    fileMenu = new QMenu(QString("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openWebcamAction);
    menuBar()->addMenu(fileMenu);

    // Effect Menu
    effectMenu = new QMenu(QString("&Effect"));
    effectMenu->addAction(morphAction);
    effectMenu->addAction(circleDetectorAction);
    effectMenu->addAction(dotPatternAction);
    menuBar()->addMenu(effectMenu);

    // Help Menu
    helpMenu = new QMenu(QString("&Help"));
    helpMenu->addAction(aboutAction);
    menuBar()->addMenu(helpMenu);

}

void MainWindow::createStatusBar()
{
    xyLabel = new QLabel(QString("        "));
    statusBar()->addWidget(xyLabel,0);
}

void MainWindow::createDockWidget()
{
    rightDock = new QDockWidget(QString("Properties"),this);
    bottomDock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea,rightDock);
    bottomDock->setWidget(logTxtEdit);
    addDockWidget(Qt::BottomDockWidgetArea,bottomDock);

}

void MainWindow::createFilter()
{
    circleFitler = new CircleFilter();
    circleFitler->setLogText(logTxtEdit);
    morphFilter = new MorphOperations();
    morphFilter->setLogText(logTxtEdit);
    rectangleFilter = new RectangleFilter();
    rectangleFilter->setLogText(logTxtEdit);
    circleDetectorFilter = new CircleDetectorFilter();
    circleDetectorFilter->setLogText(logTxtEdit);
    dotPatternFilter = new DotPatternFilter();
    dotPatternFilter->setLogText(logTxtEdit);

}

void MainWindow::updateDock()
{
    if(currentFilter != NULL){
        rightDock->setWidget(currentFilter->getWidget());
        //rightDock->adjustSize();
        setFixedSize(sizeHint());
    }
}

void MainWindow::createToolBar()
{
    leftToolBar = new QToolBar(this);
    leftToolBar->addAction(circleAction);
    leftToolBar->addAction(rectangleAction);
    addToolBar(Qt::LeftToolBarArea, leftToolBar);
    leftToolBar->setMovable(false);
}
