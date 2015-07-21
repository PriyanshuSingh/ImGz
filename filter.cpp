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
    originalImg = im.clone();
    processedImg = im.clone();
    emit imageChanged();
}

void Filter::appendLog(QString message)
{
    logTxt->appendPlainText(message);
}

void Filter::setLogText(QPlainTextEdit *logTxt)
{
    this->logTxt = logTxt;
}

