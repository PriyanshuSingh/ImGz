#include "circlefilter.h"
#include <QPoint>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QObject>
#include "filter.h"
#include <cmath>
#include <QLabel>
#include <QVBoxLayout>



CircleFilter::CircleFilter():Filter()
{
    thicknessSpinBox=new QSpinBox;
    thicknessSpinBox->setRange(0,100);
    thicknessSpinBox->setSingleStep(1);
    thicknessSpinBox->setValue(0);

    filledCheckBox = new QCheckBox(QString("Filled"));
    setNewCircleInProgress(false);
    createPropertyWidget();

    connect(thicknessSpinBox,SIGNAL(valueChanged(int)),this,SLOT(updateThickness(int)));
    connect(filledCheckBox,SIGNAL(toggled(bool)),this,SLOT(setFilledCircle(bool)));
}

void CircleFilter::mouseMoved(QMouseEvent *ev)
{
    if(isNewCircleInProgress()){
        int x = ev->pos().x();
        int y = ev->pos().y();
        radius = sqrt((center.x() - x)*(center.x() -x) + (center.y() - y)*(center.y() - y));
    }
}

void CircleFilter::setFilledCircle(bool value)
{
    thicknessSpinBox->setEnabled(!value);
    thickness = (value)?-1:thicknessSpinBox->value();
}

bool CircleFilter::isNewCircleInProgress() const
{
    return newCircleInProgress;
}

void CircleFilter::setNewCircleInProgress(bool value)
{
    newCircleInProgress = value;
}

void CircleFilter::mousePressed(QMouseEvent *ev)
{
    setNewCircleInProgress(true);
    center = ev->pos();
    radius = 0;
}

void CircleFilter::mouseReleased(QMouseEvent *ev)
{
    if(isNewCircleInProgress()){
        setNewCircleInProgress(false);
        int x = ev->pos().x();
        int y = ev->pos().y();
        radius = sqrt((center.x() - x)*(center.x() -x) + (center.y() - y)*(center.y() - y));
        processedImg = originalImg.clone();
        cv::circle(processedImg, cv::Point(center.x(),center.y()), radius+1, cv::Scalar(100,200,250),thickness);
    }
}

cv::Mat CircleFilter::getImage()
{
    if(isNewCircleInProgress()){
        return processedImg;
    }
    return originalImg;
}

void CircleFilter::applyFilter()
{
    if(isNewCircleInProgress()){
        originalImg.copyTo(processedImg);
        cv::circle(processedImg, cv::Point(center.x(),center.y()), radius+1, cv::Scalar(100,200,250),thickness);
    }else{
        processedImg.copyTo(originalImg);
    }
}

void CircleFilter::updateThickness(int i){
    thickness=i;
}

void CircleFilter::createPropertyWidget(){

    propertyWidget =new QWidget();
    QFormLayout *FLayout = new QFormLayout();
    FLayout->addRow(QString("Thickness"),thicknessSpinBox);
    FLayout->addWidget(filledCheckBox);
    propertyWidget->setLayout(FLayout);
    propertyWidget->setFixedSize(propertyWidget->sizeHint());
    propertyWidget->setStyleSheet("background-color:grey");
}




