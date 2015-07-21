#include "filter.h"
#include "rectanglefilter.h"
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

RectangleFilter::RectangleFilter():Filter()
{
    thicknessSpinBox=new QSpinBox;
    thicknessSpinBox->setRange(0,100);
    thicknessSpinBox->setSingleStep(1);
    thicknessSpinBox->setValue(0);

    filledCheckBox = new QCheckBox(QString("Filled"));
    setNewRectangleInProgress(false);
    createPropertyWidget();

    connect(thicknessSpinBox,SIGNAL(valueChanged(int)),this,SLOT(updateThickness(int)));
    connect(filledCheckBox,SIGNAL(toggled(bool)),this,SLOT(setFilledRectangle(bool)));
}

cv::Mat RectangleFilter::getImage()
{
    if(isNewRectangleInProgress()){
        return processedImg;
    }
    return originalImg;
}

void RectangleFilter::applyFilter()
{
    if(isNewRectangleInProgress()){
        originalImg.copyTo(processedImg);
        cv::rectangle(processedImg,cv::Point2i(pt1.x(),pt1.y()),cv::Point2i(pt2.x(),pt2.y()),cv::Scalar(100,100,100),thickness);
    }else{
        processedImg.copyTo(originalImg);
    }
}
bool RectangleFilter::isNewRectangleInProgress() const
{
    return newRectangleInProgress;
}

void RectangleFilter::setNewRectangleInProgress(bool value)
{
    newRectangleInProgress = value;
}

void RectangleFilter::updateThickness(int i)
{
    thickness=i;
}

void RectangleFilter::mousePressed(QMouseEvent *ev)
{
    if(!isNewRectangleInProgress()){
        setNewRectangleInProgress(true);
        pt1 = ev->pos();
        pt2 = ev->pos();
    }
}

void RectangleFilter::mouseReleased(QMouseEvent *ev)
{
    if(isNewRectangleInProgress()){
        setNewRectangleInProgress(false);
        pt2.setX(ev->pos().x());
        pt2.setY(ev->pos().y());
        originalImg.copyTo(processedImg);
        cv::rectangle(processedImg,cv::Point2i(pt1.x(),pt1.y()),cv::Point2i(pt2.x(),pt2.y()),cv::Scalar(100,100,100),thickness);
    }
}

void RectangleFilter::mouseMoved(QMouseEvent *ev)
{
    if(isNewRectangleInProgress()){
        pt2.setX(ev->pos().x());
        pt2.setY(ev->pos().y());
    }
}

void RectangleFilter::setFilledRectangle(bool val)
{
    thicknessSpinBox->setEnabled(!val);
    thickness = (val)?-1:thicknessSpinBox->value();
}

void RectangleFilter::createPropertyWidget()
{
    propertyWidget =new QWidget();
    QFormLayout *FLayout = new QFormLayout();
    FLayout->addRow(QString("Thickness"),thicknessSpinBox);
    FLayout->addWidget(filledCheckBox);
    propertyWidget->setLayout(FLayout);
    propertyWidget->setFixedSize(propertyWidget->sizeHint());
    propertyWidget->setStyleSheet("background-color:grey");
}


