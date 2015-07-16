#include "filter.h"

Filter::Filter()
{

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

