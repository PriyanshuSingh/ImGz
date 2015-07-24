#include "facedetector.h"
#include <QPoint>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>

#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QFormLayout>
#include <QObject>
#include <QLabel>
#include <QVBoxLayout>
#include <vector>
#include <QSlider>

FaceDetector::FaceDetector()
{

    bool ok = frontalFaceCascade.load("/home/priyanshu/opencv/opencv-3.0.0/data/lbpcascades/lbpcascade_frontalface.xml");
    ok = ok & profileFaceCascade.load("/home/priyanshu/opencv/opencv-3.0.0/data/lbpcascades/lbpcascade_profileface.xml");

    medianBlurSizeSlider = new QSlider(Qt::Horizontal);
    medianBlurSizeSlider->setTickInterval(100);
    medianBlurSizeSlider->setFocusPolicy(Qt::StrongFocus);
    medianBlurSizeSlider->setSingleStep(2);
    medianBlurSizeSlider->setRange(1,9);
    medianBlurSizeSlider->setTickPosition(QSlider::TicksBothSides);

    rectThresholdSpinBox = new QSpinBox();
    rectThresholdSpinBox->setRange(0,10);

    //sharpnessFilter = new SharpnessFilter();
    dotPatternFilter = new DotPatternFilter();

    initPropertiesValues();

    connect(medianBlurSizeSlider,SIGNAL(valueChanged(int)),this,SLOT(updateMedianBlurSizeSlider(int)));
    connect(rectThresholdSpinBox,SIGNAL(valueChanged(int)),this,SLOT(updateRectThresholdSpinBox(int)));
    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
    createPropertyWidget();
}

cv::Mat FaceDetector::getImage()
{
    return processedImg;
}

void FaceDetector::applyFilter()
{
    static int a = 0;
    dotPatternFilter->setLogText(logTxt);
    if(isChanged()){
        faces.clear();
        tempfaces.clear();
        cv::medianBlur(grayImgMat,grayImgMat,medianBlurSize);

        if(!frontalFaceCascade.empty()){
            frontalFaceCascade.detectMultiScale(grayImgMat,faces,1.1,rectThreshold);
        }
        if(!profileFaceCascade.empty()){
            profileFaceCascade.detectMultiScale(grayImgMat,tempfaces,1.1,rectThreshold);
            for(int i=0; i<tempfaces.size();++i){
                faces.push_back(tempfaces[i]);
            }
        }
        originalImg.copyTo(processedImg);
        for(int i=0; i<faces.size(); ++i){
            cv::rectangle(processedImg,faces[i],cv::Scalar(0,0,0),3,8,0);
            cv::Mat temp(processedImg,faces[i]);
            dotPatternFilter->setImage(temp);
            dotPatternFilter->applyFilter();
            temp = dotPatternFilter->getImage();
            temp.copyTo(processedImg(faces[i]));
        }
        setChanged(false);
    }
}

void FaceDetector::initPropertiesValues()
{

    rectThreshold = 3;
    rectThresholdSpinBox->setValue(3);
    medianBlurSize = 3;
    medianBlurSizeSlider->setValue(3);

}

void FaceDetector::mouseReleased(QMouseEvent *ev)
{

}

void FaceDetector::mousePressed(QMouseEvent *ev)
{

}

void FaceDetector::mouseMoved(QMouseEvent *ev)
{

}

void FaceDetector::handleImageChanged()
{
    cv::cvtColor(originalImg,grayImgMat,CV_BGR2GRAY);
    somethingChanged();
}

void FaceDetector::somethingChanged()
{
    setChanged(true);
}

void FaceDetector::updateMedianBlurSizeSlider(int val)
{
    medianBlurSize = val;
    somethingChanged();
}

void FaceDetector::updateRectThresholdSpinBox(int val)
{
    rectThreshold = val;
    somethingChanged();
}

void FaceDetector::createPropertyWidget()
{
    propertyWidget = new QWidget();
    QVBoxLayout *jj = new QVBoxLayout();
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addRow(QString("blur Size"),medianBlurSizeSlider);
    fLayout->addRow(QString("rect threshold"),rectThresholdSpinBox);
    jj->addLayout(fLayout);
    jj->addWidget(dotPatternFilter->getWidget());
    propertyWidget->setLayout(jj);
}
bool FaceDetector::isChanged() const
{
    return changed;
}

void FaceDetector::setChanged(bool value)
{
    changed = value;
}


