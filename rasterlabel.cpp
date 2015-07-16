#include "rasterlabel.h"
#include <QTimer>
#include <QImage>
#include <iostream>

RasterLabel::RasterLabel(QWidget *parent):QLabel(parent)
{

    tmr = new QTimer(parent);
    connect(tmr,SIGNAL(timeout()),this, SLOT(rr()));
}

RasterLabel::~RasterLabel()
{

}

void RasterLabel::rr()
{
    imgMat = filter->getImage();
    QImage qimg((uchar*)imgMat.data, imgMat.cols, imgMat.rows, imgMat.step, QImage::Format_RGB888);
    setPixmap(QPixmap::fromImage(qimg));
}

void RasterLabel::setImage(cv::Mat img)
{
    imgMat = img;
}

void RasterLabel::setFilter(Filter *filter){
    this->filter = filter;
}

void RasterLabel::initRender()
{
    tmr->start(50);
}

void RasterLabel::stopRender()
{
    tmr->stop();
}

void RasterLabel::mouseMoveEvent(QMouseEvent *ev)
{
    filter->mouseMoved(ev);
}

void RasterLabel::mousePressEvent(QMouseEvent *ev)
{
    filter->mousePressed(ev);
}

void RasterLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    filter->mouseReleased(ev);
}
