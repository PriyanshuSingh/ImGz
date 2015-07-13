#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QtCore>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    capWebcam.open(0);
    capWebcam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capWebcam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    if(!capWebcam.isOpened()){
        ui->logPlainText->appendPlainText("ERROR: capWebcam not accessed successfuly");
        return;
    }
    // filling combo box
    fillComboBoxWithFilters();
    currentFilter = ORIGINAL;

    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGui()));
    tmrTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFrameAndUpdateGui(){
    capWebcam.read(matOriginal);
    if(matOriginal.empty())return;

    matProcessed = matOriginal.clone();

    if(currentFilter == ORIGINAL){
        cv::cvtColor(matOriginal,matOriginal, CV_BGR2RGB);
        cv::cvtColor(matProcessed,matProcessed,CV_BGR2RGB);
    }
    else if(currentFilter == CANNY_EDGES){
        cv::cvtColor(matProcessed,matProcessed, CV_BGR2GRAY);
        cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9,9), 1.5);
        cv::Canny(matProcessed,matProcessed, 0, 30, 3);
        cv::cvtColor(matOriginal,matOriginal, CV_BGR2RGB);
        cv::cvtColor(matProcessed,matProcessed,CV_GRAY2RGB);
    }
    else if(currentFilter == BOX_BLUR){
        cv::blur(matProcessed,matProcessed,cv::Size(9,9));
        cv::cvtColor(matOriginal,matOriginal, CV_BGR2RGB);
        cv::cvtColor(matProcessed,matProcessed,CV_BGR2RGB);
    }
    else if(currentFilter == GAUSSIAN_BLUR){
        cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9,9), 1.5);
        cv::cvtColor(matOriginal,matOriginal, CV_BGR2RGB);
        cv::cvtColor(matProcessed,matProcessed,CV_BGR2RGB);
    }

    QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_RGB888);

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->lblProcessed->setPixmap(QPixmap::fromImage(qimgProcessed));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->logPlainText->appendPlainText("selected " + ui->cmboBoxFilter->currentText());
    currentFilter = ui->cmboBoxFilter->currentIndex();
}

void MainWindow::fillComboBoxWithFilters(){
    for(int i=0; i<COMBO_BOX_LENGTH; i++){
        if(i == ORIGINAL){
            ui->cmboBoxFilter->addItem("Original");
        }else if(i == BOX_BLUR){
            ui->cmboBoxFilter->addItem("Box Blur");
        }else if(i == GAUSSIAN_BLUR){
            ui->cmboBoxFilter->addItem("Gaussian Blur");
        }else if(i == CANNY_EDGES){
            ui->cmboBoxFilter->addItem("Canny Edges");
        }
    }
}
