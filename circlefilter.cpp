#include "circlefilter.h"
#include <QPoint>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QObject>
#include "filter.h"
#include "circlefilter.h"
#include <cmath>



CircleFilter::CircleFilter():Filter()
{
    thickn=new QSpinBox;
    thickn->setRange(0,100);
    thickn->setSingleStep(1);
    thickn->setValue(0);
    connect(thickn,SIGNAL(valueChanged(int)),this,SLOT(updateThickness(int)));

}
void CircleFilter::mouseMoved(QMouseEvent *ev)
{
    setProcessed(false);
    int x = ev->pos().x();
    int y = ev->pos().y();
    int radius = sqrt((center.x() - x)*(center.x() -x) + (center.y() - y)*(center.y() - y));
    tempImg = originalImg.clone();
    if(okToContiue && centerDefined){
        cv::circle(tempImg, cv::Point(center.x(),center.y()), radius+1, cv::Scalar(100,200,250),thickness);
    }
    processedImg = tempImg;
    setProcessed(true);
}

void CircleFilter::mousePressed(QMouseEvent *ev)
{
    centerDefined = true;
    center = ev->pos();
    okToContiue = true;
}

void CircleFilter::mouseReleased(QMouseEvent *ev)
{
    radiusDefined = true;
    if(centerDefined){
        int x = ev->pos().x();
        int y = ev->pos().y();
        int radius = sqrt((center.x() - x)*(center.x() -x) + (center.y() - y)*(center.y() - y));
            tempImg = originalImg.clone();
        cv::circle(tempImg, cv::Point(center.x(),center.y()), radius+1, cv::Scalar(100,200,250),thickness);
    }
    originalImg = tempImg;
    processedImg = tempImg;
    centerDefined = radiusDefined = okToContiue = false;
}

cv::Mat CircleFilter::getImage()
{
    if(isProcessed()){
        return processedImg;
    }
    return originalImg;
}

void CircleFilter::updateThickness(int i){
    thickness=i;
}

void CircleFilter::updateBottomDock(QDockWidget *dock, QWidget *parent){
    //dock = new QDockWidget(parent);
    QWidget *j=new QWidget();
    j->setStyleSheet("background-color:red;");
    dock->setWidget(j);

    dock->setWidget(thickn);

    //parent->addDockWidget(Qt::BottomDockWidgetArea,dock);
}




