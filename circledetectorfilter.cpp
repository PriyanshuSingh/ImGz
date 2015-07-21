#include "circledetectorfilter.h"
#include "filter.h"
#include <QPoint>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QFormLayout>
#include <QObject>
#include <QLabel>
#include <QVBoxLayout>
#include <vector>
#include <QSlider>


CircleDetectorFilter::CircleDetectorFilter()
{
    upperThresholdSlider = new QSlider(Qt::Horizontal);
    upperThresholdSlider->setFocusPolicy(Qt::StrongFocus);
    upperThresholdSlider->setTickPosition(QSlider::TicksBothSides);
    upperThresholdSlider->setTickInterval(100);
    upperThresholdSlider->setRange(80,300);
    upperThresholdSlider->setSingleStep(1);
    upperThresholdSlider->setValue(120);

    lowerThresholdSlider = new QSlider(Qt::Horizontal);
    lowerThresholdSlider->setFocusPolicy(Qt::StrongFocus);
    lowerThresholdSlider->setTickPosition(QSlider::TicksBothSides);
    lowerThresholdSlider->setTickInterval(100);
    lowerThresholdSlider->setSingleStep(1);
    lowerThresholdSlider->setRange(1,300);
    lowerThresholdSlider->setValue(40);
    upperThreshold = 120;
    lowerThreshold = 40;
    createPropertyWidget();
    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
    connect(upperThresholdSlider,SIGNAL(valueChanged(int)),this,SLOT(updateUpperThreshold(int)));
    connect(lowerThresholdSlider,SIGNAL(valueChanged(int)),this,SLOT(updateLowerThreshold(int)));
}

bool CircleDetectorFilter::isChanged() const
{
    return changed;
}

void CircleDetectorFilter::setChanged(bool value)
{
    changed = value;
}

void CircleDetectorFilter::applyFilter()
{
    if(isChanged()){
        circles.empty();
        cv::GaussianBlur(grayImgMat, grayImgMat, cv::Size(3, 3), 2, 2 );
        cv::HoughCircles(grayImgMat,circles, CV_HOUGH_GRADIENT, 1, grayImgMat.rows/16, upperThreshold, 100, 0, 0);

        for(size_t i=0; i < circles.size(); i++){
            cv::Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            cv::circle(processedImg,center,3,cv::Scalar(0,255,0), -1, 8, 0);
            cv::circle(processedImg,center,radius, cv::Scalar(0,0,255), 3, 8, 0);
        }
    }
}

void CircleDetectorFilter::mouseMoved(QMouseEvent *ev)
{
    
}

void CircleDetectorFilter::mousePressed(QMouseEvent *ev)
{
    
}

void CircleDetectorFilter::mouseReleased(QMouseEvent *ev)
{
    
}

cv::Mat CircleDetectorFilter::getImage()
{
    return processedImg;
}

void CircleDetectorFilter::somethingChanged()
{
    setChanged(true);
    
}

void CircleDetectorFilter::handleImageChanged()
{
    cv::cvtColor(originalImg, grayImgMat, CV_BGR2GRAY);
    originalImg.copyTo(processedImg);
    somethingChanged();
}

void CircleDetectorFilter::updateUpperThreshold(int  thresh)
{
    if(thresh < lowerThreshold + 5){
        upperThreshold = lowerThreshold + 5;
        upperThresholdSlider->setValue(upperThreshold);
    }else{
        upperThreshold = thresh;
    }
    appendLog(QString("Upper threshold: ")+QString::number(upperThreshold));
    if(thresh < 90){
        appendLog(QString("upper threshold below 90 is cpu intensive"));

    }
    somethingChanged();

}

void CircleDetectorFilter::updateLowerThreshold(int thresh)
{
    if(thresh > upperThreshold - 5){
        lowerThreshold = upperThreshold - 5;
        lowerThresholdSlider->setValue(lowerThreshold);
    }else{
        lowerThreshold = thresh;
    }
    appendLog(QString("Upper threshold: ")+QString::number(lowerThreshold));
    somethingChanged();
}

void CircleDetectorFilter::createPropertyWidget()
{
    propertyWidget = new QWidget();
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addRow(QString("Upper Threshold"),upperThresholdSlider);
    fLayout->addRow(QString("Lower Threshold"),lowerThresholdSlider);
    propertyWidget->setLayout(fLayout);
}


