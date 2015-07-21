#include "dotpatternfilter.h"
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

DotPatternFilter::DotPatternFilter():Filter()
{
    squareSize = 10;
    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
}

void DotPatternFilter::applyFilter()
{
    if(isChanged()){
        std::vector<cv::Mat> channels;
        cv::split(destMat_32f, channels);
        for(int i=0; i<channels.size(); ++i){
            channels[i] = channels[i].mul(patternMaskMat);
        }
        cv::merge(channels, destMat_32f);
        destMat_32f.convertTo(processedImg, CV_8U);
        setChanged(true);
    }
}

void DotPatternFilter::mouseMoved(QMouseEvent *ev)
{

}

void DotPatternFilter::mousePressed(QMouseEvent *ev)
{

}

void DotPatternFilter::mouseReleased(QMouseEvent *ev)
{

}

cv::Mat DotPatternFilter::getImage()
{
    return processedImg;
}

void DotPatternFilter::createPatternMask()
{
    if(patternMaskMat.empty() || patternMaskMat.rows != originalImg.rows || patternMaskMat.cols != originalImg.cols){
        cv::Mat pttrn = cv::Mat::zeros(originalImg.size(), CV_8UC1);
        for(int i = 0; i < originalImg.rows; i += squareSize){
            for(int j = 0; j < originalImg.cols; j += squareSize){
                cv::circle(pttrn,cv::Point(j+squareSize/2,i+squareSize/2),squareSize/2-1,cv::Scalar(255,255,255));
            }
        }
        pttrn.convertTo(patternMaskMat, CV_32F);
        cv::normalize(patternMaskMat,patternMaskMat, 0, 1, cv::NORM_MINMAX);
        somethingChanged();
    }

}

void DotPatternFilter::createPixelattedImage()
{
    destMat = cv::Mat::zeros(originalImg.size(), CV_8UC3);
    for(int i = 0; i < originalImg.rows; i += squareSize){
        for(int j = 0; j < originalImg.cols; j += squareSize){
            cv::Rect rect = cv::Rect(j, i, squareSize, squareSize) &
                    cv::Rect(0, 0, originalImg.cols, originalImg.rows);
            cv::Mat subDestMat(destMat, rect);
            subDestMat.setTo(cv::mean(originalImg(rect)));
        }
    }
    destMat.convertTo(destMat_32f, CV_32F);
    somethingChanged();
}
bool DotPatternFilter::isChanged() const
{
    return changed;
}

void DotPatternFilter::setChanged(bool value)
{
    changed = value;
}

void DotPatternFilter::somethingChanged()
{
    setChanged(true);
}

void DotPatternFilter::handleImageChanged()
{
    createPatternMask();
    createPixelattedImage();

}


