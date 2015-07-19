#include "morphOperations.h"
#include "filter.h"
#include <QVBoxLayout>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include<iostream>
MorphOperations::MorphOperations():Filter()
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

void MorphOperations::updateBottomDock(QDockWidget *dock, QWidget *parent){

    originalImg.copyTo(tempImage);      //Temp image set to be used in applyFilter

    QWidget *window=new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *kernelLabel = new QLabel();         //Kernel Size widgets
    kernelLabel->setText("Kernal Size(2n+1)");
    layout->addWidget(kernelLabel);
    layout->addWidget(kSizeSpinBox);

    QLabel *elementLabel=new QLabel;           //Element Type Widgets
    elementLabel->setText("Kernel Shape");
    layout->addWidget(elementLabel);
    layout->addWidget(morphElementComboBox);

    QLabel *morphOperation = new QLabel;
    morphOperation->setText("Morphological Transformation");
    layout->addWidget(morphOperation);
    layout->addWidget(morphTypeComboBox);


    window->setLayout(layout);
    dock->setWidget(window);
}

void MorphOperations::updateKernelSize(int i){
    this->kSize=i;
    this->applyFilter();        //Filter applied with updated kernel size
}

void MorphOperations::updateMorphElement(int elementType){
    this->element=elementType;
    this->applyFilter();        //Filter applied with updated element type
}

void MorphOperations::updateMorphOperation(int morphOpType){
    switch (morphOpType) {
    case 0:                     // morph operation - Opening
        morphOperationType = 2;
        applyFilter();
        break;
    case 1:                     // morph operation - Closing
        morphOperationType = 3;
        applyFilter();
        break;
    case 2:                     // morph operation - Morphological gradient
        morphOperationType = 4;
        applyFilter();
        break;
    default:
        break;
    }
}

void MorphOperations::applyFilter(){
    setProcessed(false);
    cv::Mat strElement = getStructuringElement( element, cv::Size( 2*kSize + 1, 2*kSize+1 ), cv::Point( kSize, kSize));
    cv::morphologyEx( tempImage, processedImg, morphOperationType, strElement);
    setProcessed(true);
}

cv::Mat MorphOperations::getImage()
{
    if(isProcessed()){
        return processedImg;
    }
    return originalImg;
}

void MorphOperations::mouseMoved(QMouseEvent *ev){

}

void MorphOperations::mousePressed(QMouseEvent *ev){

}

void MorphOperations::mouseReleased(QMouseEvent *ev){

}


