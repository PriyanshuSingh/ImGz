#include "sharpnessfilter.h"
#include "filter.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include<iostream>

SharpnessFilter::SharpnessFilter():Filter()
{
    createPropertyWidget();
    connect(this,SIGNAL(imageChanged()),this,SLOT(somethingChanged()));
}

void SharpnessFilter::updateSharpType(int type){

    switch (type) {
    case 0:
        noneType = true;
        somethingChanged();
    case 1:                     //Very fine
        noneType = false;
        kernal = (cv::Mat_<char>(4,4) <<   0.272, 0.534, 0.131, 0,
                     0.349, 0.686, 0.168, 0,
                     0.393, 0.769, 0.189, 0,
                     0, 0, 0, 1);
        cv::filter2D(originalImg, tempImage, originalImg.depth(), kernal);
        somethingChanged();
        break;
    case 2:                     // Fine
        noneType = false;
        medianBlur(originalImg, tempImage, 3);
        somethingChanged();
        break;
    case 3:                     // Coarse
        noneType = false;
        GaussianBlur(originalImg, tempImage, cv::Size(0, 0), 3);
        somethingChanged();
        break;
    default:
        break;
    }
}

void SharpnessFilter::applyFilter(){
    if(isChanged()){
        /*if(noneType){
            processedImg = tempOriginalImg.clone();
        }*/
        if(!tempImage.empty()){
            cv::addWeighted(originalImg,1.7,tempImage,-0.7,0,processedImg);
        }
        setChanged(false);
    }
}


cv::Mat SharpnessFilter::getImage()
{
    return processedImg;
}

void SharpnessFilter::createPropertyWidget()
{
    createProperties();

    propertyWidget = new QWidget();

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Sharpness Level",sharpTypeComboBox);
    propertyWidget->setLayout(formLayout);
    propertyWidget->setFixedSize(propertyWidget->sizeHint());
}

void SharpnessFilter::createProperties(){
    sharpTypeComboBox = new QComboBox;
    sharpTypeComboBox->addItem("None");
    sharpTypeComboBox->addItem("Very Fine");
    sharpTypeComboBox->addItem("Fine");
    sharpTypeComboBox->addItem("Coarse");
    sharpTypeComboBox->setCurrentText("None");
    connect(sharpTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateSharpType(int)));
    //tempOriginalImg = originalImg.clone();
}

void SharpnessFilter::somethingChanged(){
    setChanged(true);
}

void SharpnessFilter::setChanged(bool value){
    changed = value;
}

bool SharpnessFilter::isChanged() const{
    return changed;
}

void SharpnessFilter::mousePressed(QMouseEvent *ev){

}

void SharpnessFilter::mouseReleased(QMouseEvent *ev){

}


void SharpnessFilter::mouseMoved(QMouseEvent *ev){

}



