#include "morphOperations.h"
#include "filter.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include<iostream>
MorphOperations::MorphOperations():Filter()
{
    createPropertyWidget();
    connect(this,SIGNAL(imageChanged()),this,SLOT(somethingChanged()));
}


void MorphOperations::updateKernelSize(int i){
    this->kSize=i;
    somethingChanged();        //Filter applied with updated kernel size
}

void MorphOperations::updateMorphElement(int elementType){
    this->element=elementType;
    somethingChanged();       //Filter applied with updated element type
}

void MorphOperations::updateMorphOperation(int morphOpType){
    switch (morphOpType) {
    case 0:                     // morph operation - Opening
        morphOperationType = 2;
        somethingChanged();
        break;
    case 1:                     // morph operation - Closing
        morphOperationType = 3;
        somethingChanged();
        break;
    case 2:                     // morph operation - Morphological gradient
        morphOperationType = 4;
        somethingChanged();
        break;
    default:
        break;
    }
}

void MorphOperations::applyFilter(){
    if(isChanged()){
        originalImg.copyTo(tempImage);
        if(!tempImage.empty()){
            cv::Mat strElement = getStructuringElement(element, cv::Size( 2*kSize + 1, 2*kSize+1 ), cv::Point( kSize, kSize));
            cv::morphologyEx(tempImage, processedImg, morphOperationType, strElement);
        }
        setChanged(false);
    }
}


cv::Mat MorphOperations::getImage()
{
    return processedImg;
}

void MorphOperations::createPropertyWidget()
{
    createProperties();

    propertyWidget = new QWidget();

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Kernal Size(2n+1)",kSizeSpinBox);
    formLayout->addRow(QString("Kernal Size"),morphElementComboBox);
    formLayout->addRow(QString("Morphological\nTransformation"),morphTypeComboBox);

    propertyWidget->setLayout(formLayout);
    propertyWidget->setFixedSize(propertyWidget->sizeHint());
}

void MorphOperations::createProperties()
{
    kSizeSpinBox=new QSpinBox;
    kSizeSpinBox->setRange(0,21);
    kSizeSpinBox->setSingleStep(1);
    kSizeSpinBox->setValue(0);
    connect(kSizeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(updateKernelSize(int))); //kernel Size updated

    morphElementComboBox = new QComboBox;
    morphElementComboBox->addItem("Rect");         //index 0 (MORPH_RECT)
    morphElementComboBox->addItem("Cross");         //index 1 (MORPH_CROSS)
    morphElementComboBox->addItem("Ellipse");       //index 2 (MORPH_ELLIPSE)
    morphElementComboBox->setCurrentText("Rect");
    element = 0;
    connect(morphElementComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMorphElement(int)));

    morphTypeComboBox = new QComboBox;
    morphTypeComboBox->addItem("Opening");
    morphTypeComboBox->addItem("Closing");
    morphTypeComboBox->addItem("Morphological Gradient");
    morphTypeComboBox->setCurrentText("Opening");
    morphOperationType=2;       //Morph operations have indices starting from 2
    connect(morphTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMorphOperation(int)));
}

void MorphOperations::mousePressed(QMouseEvent *ev){

}

void MorphOperations::mouseReleased(QMouseEvent *ev){

}


void MorphOperations::mouseMoved(QMouseEvent *ev){

}

void MorphOperations::somethingChanged()
{
    setChanged(true);
}

bool MorphOperations::isChanged() const
{
    return changed;
}

void MorphOperations::setChanged(bool value)
{
    changed = value;
}


