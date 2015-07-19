#include "rasterlabel.h"
#include <QTimer>
#include <QImage>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
RasterLabel::RasterLabel(QWidget *parent):QLabel(parent)
{

    tmr = new QTimer(parent);
    connect(tmr,SIGNAL(timeout()),this, SLOT(renderImage()));
    connect(this,SIGNAL(nothingToDisplay()), this, SLOT(noDisplayableImage()));
    setMouseTracking(true);
    filter = NULL;
    tmr->start(50);
}

RasterLabel::~RasterLabel()
{

}

void RasterLabel::renderImage()
{

    if(isImgDefined()){
        if(isFilterDefined()){
            imgMat = filter->getImage();
        }
        // Converting Image to RGB2BGR
        cv::Mat displayMat;
        cvtColor(imgMat, displayMat, CV_BGR2RGB);
        QImage qimg((uchar*)displayMat.data, imgMat.cols, imgMat.rows, imgMat.step, QImage::Format_RGB888);
        setPixmap(QPixmap::fromImage(qimg));
    }else{
        tmr->stop();
        emit nothingToDisplay();
    }
}

void RasterLabel::noDisplayableImage()
{
    setFixedSize(QSize(500,500));
    setStyleSheet("background-color:gray");
}

bool RasterLabel::isImgDefined() const
{
    return !imgMat.empty();
}

bool RasterLabel::isFilterDefined() const
{
    return filter != NULL;
}

void RasterLabel::setImage(cv::Mat img)
{
    imgMat = img;
    if(isImgDefined()){
        if(tmr->isActive() == false)tmr->start(50);
        setFixedSize(QSize(imgMat.rows,imgMat.cols));
        if(isFilterDefined())this->filter->setImage(imgMat);
    }
}

void RasterLabel::setFilter(Filter *filter){

    if(isFilterDefined()){
        disconnect(this,SIGNAL(mouseMoved(QMouseEvent*)),this->filter,SLOT(mouseMoved(QMouseEvent*)));
        disconnect(this,SIGNAL(mousePressed(QMouseEvent*)),this->filter,SLOT(mousePressed(QMouseEvent*)));
        disconnect(this,SIGNAL(mouseReleased(QMouseEvent*)),this->filter,SLOT(mouseReleased(QMouseEvent*)));

    }
    this->filter = filter;
    if(isImgDefined() && isFilterDefined())this->filter->setImage(imgMat);
    if(isFilterDefined()){
        connect(this,SIGNAL(mouseMoved(QMouseEvent*)),this->filter,SLOT(mouseMoved(QMouseEvent*)));
        connect(this,SIGNAL(mousePressed(QMouseEvent*)),this->filter,SLOT(mousePressed(QMouseEvent*)));
        connect(this,SIGNAL(mouseReleased(QMouseEvent*)),this->filter,SLOT(mouseReleased(QMouseEvent*)));
    }

}

void RasterLabel::mouseMoveEvent(QMouseEvent *ev)
{
    emit mouseMoved(ev);
}

void RasterLabel::mousePressEvent(QMouseEvent *ev)
{
    emit mousePressed(ev);
}

void RasterLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit mouseReleased(ev);
}
