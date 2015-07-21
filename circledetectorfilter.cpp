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

CircleDetectorFilter::CircleDetectorFilter()
{

    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
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
        cv::GaussianBlur(grayImgMat, grayImgMat, cv::Size(9, 9), 2, 2 );
        cv::HoughCircles(grayImgMat,circles, CV_HOUGH_GRADIENT, 1, grayImgMat.rows/16, 150, 100, 0, 0);

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


