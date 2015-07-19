#include "openingfilter.h"
#include "filter.h"
#include <QVBoxLayout>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include<iostream>
OpeningFilter::OpeningFilter():Filter()
{


    kernelSize=new QSpinBox;
    kernelSize->setRange(0,21);
    kernelSize->setSingleStep(1);
    kernelSize->setValue(0);
    connect(kernelSize,SIGNAL(valueChanged(int)),this,SLOT(updateKernelSize(int))); //kernel Size updated

    morphElement = new QComboBox;
    morphElement->addItem("Rect");         //index 0 (MORPH_RECT)
    morphElement->addItem("Cross");         //index 1 (MORPH_CROSS)
    morphElement->addItem("Ellipse");       //index 2 (MORPH_ELLIPSE)
    morphElement->setCurrentText("Rect");
    element = 0;
    connect(morphElement,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMorphElement(int)));
}

void OpeningFilter::updateBottomDock(QDockWidget *dock, QWidget *parent){

    originalImg.copyTo(tempImage);      //Temp image set to be used in applyFilter

    QWidget *window=new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *kernelLabel = new QLabel();         //Kernel Size widgets
    kernelLabel->setText("Kernal Size(2n+1)");
    layout->addWidget(kernelLabel);
    layout->addWidget(kernelSize);

    QLabel *elementLabel=new QLabel;           //Element Type Widgets
    elementLabel->setText("Kernel Shape");
    layout->addWidget(elementLabel);
    layout->addWidget(morphElement);

    window->setLayout(layout);
    dock->setWidget(window);
}

void OpeningFilter::updateKernelSize(int i){
    this->kSize=i;
    this->applyFilter();        //Filter applied with updated kernel size
}

void OpeningFilter::updateMorphElement(int elementType){
    this->element=elementType;
    this->applyFilter();        //Filter applied with updated element type
}

void OpeningFilter::applyFilter(){
    setProcessed(false);
    cv::Mat strElement = getStructuringElement( element, cv::Size( 2*kSize + 1, 2*kSize+1 ), cv::Point( kSize, kSize));
    cv::morphologyEx( tempImage, processedImg, cv::MORPH_OPEN, strElement);
    setProcessed(true);
}

cv::Mat OpeningFilter::getImage()
{
    if(isProcessed()){
        return processedImg;
    }
    return originalImg;
}

void OpeningFilter::mouseMoved(QMouseEvent *ev){

}

void OpeningFilter::mousePressed(QMouseEvent *ev){

}

void OpeningFilter::mouseReleased(QMouseEvent *ev){

}


