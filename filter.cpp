#include "filter.h"

Filter::Filter()
{

}

QWidget *Filter::getWidget()
{
    return propertyWidget;
}

bool Filter::isProcessed(){
    return imageReady;
}

void Filter::setProcessed(bool proc){
    imageReady = proc;
}

void Filter::setImage(cv::Mat im)
{
    originalImg = processedImg = im;
}

