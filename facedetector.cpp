#include "facedetector.h"
#include <QPoint>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <QStackedLayout>
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
    //frameCount = 0;

    bool ok = frontalFaceCascade.load("/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml");
    ok = ok & profileFaceCascade.load("/usr/local/share/OpenCV/lbpcascades/lbpcascade_profileface.xml");

    medianBlurSizeSlider = new QSlider(Qt::Horizontal);
    medianBlurSizeSlider->setFocusPolicy(Qt::StrongFocus);
    medianBlurSizeSlider->setSingleStep(2);
    medianBlurSizeSlider->setRange(1,9);
    medianBlurSizeSlider->setTickPosition(QSlider::NoTicks);

    rectThresholdSpinBox = new QSpinBox();
    rectThresholdSpinBox->setRange(0,10);

    filterTypeComboBox = new QComboBox;
    filterTypeComboBox->addItem("None");        //index 0, No filter applied to faces detected
    filterTypeComboBox->addItem("Morphology filters");         //index 1 (Morph operations)
    filterTypeComboBox->addItem("Sharpness");         //index 2 (Sharpness filter)
    filterTypeComboBox->addItem("Dot Pattern");       //index 3 (Dot pattern filter)
    filterTypeComboBox->setCurrentText("Sharpness");
    filterTypeComboBox->setCurrentIndex(2);
    connect(filterTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateFilterType(int)));


    sharpnessFilter = new SharpnessFilter();
    dotPatternFilter = new DotPatternFilter();
    morphFilter = new MorphOperations();
    currentFilter = sharpnessFilter;
    initPropertiesValues();

    connect(medianBlurSizeSlider,SIGNAL(valueChanged(int)),this,SLOT(updateMedianBlurSizeSlider(int)));
    connect(rectThresholdSpinBox,SIGNAL(valueChanged(int)),this,SLOT(updateRectThresholdSpinBox(int)));
    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
    createPropertyWidget();
}

void FaceDetector::updateFilterType(int i){
    switch (i) {
    case 0:
         currentFilter = NULL;
         updateFilterProperties(i);
        break;
    case 1:
        currentFilter = morphFilter;
        updateFilterProperties(i);
        break;
    case 2:
        currentFilter = sharpnessFilter;
        updateFilterProperties(i);
        break;
    case 3:
        currentFilter = dotPatternFilter;
        updateFilterProperties(i);
        break;
    default:
        currentFilter = NULL;
        updateFilterProperties(0);
        break;
    }
}

cv::Mat FaceDetector::getImage()
{
    return processedImg;
}

void FaceDetector::applyFilter()
{
    static int a = 0;
    //frameCount++;
    dotPatternFilter->setLogText(logTxt);
    //cv::flip(grayImgMat,grayImgMat,1);
    if(isChanged()){
        faces.clear();
        tempfaces.clear();
        if(medianBlurSize%2 != 1){
            appendLog(QString::number(medianBlurSize));
            medianBlurSize++;
        }
        cv::medianBlur(grayImgMat,grayImgMat,medianBlurSize);

        if(!frontalFaceCascade.empty()){
            frontalFaceCascade.detectMultiScale(grayImgMat,faces,1.1,rectThreshold,0,cv::Size(10,10));
        }
        if(!profileFaceCascade.empty()){
            profileFaceCascade.detectMultiScale(grayImgMat,tempfaces,1.1,rectThreshold,0,cv::Size(10,10));
            for(int i=0; i<tempfaces.size();++i){
                faces.push_back(tempfaces[i]);
            }
        }
        originalImg.copyTo(processedImg);
        //cv::flip(processedImg,processedImg,1);
        for(int i=0; i<faces.size(); ++i){
            cv::rectangle(processedImg,faces[i],cv::Scalar(0,0,0),3,8,0);
            cv::Mat ff(processedImg,faces[i]);
            cv::Ptr<cv::FeatureDetector> d = cv::AKAZE::create();
            std::vector<cv::KeyPoint> keypoints;
            d->detect(ff,keypoints);
            cv::drawKeypoints(ff,keypoints,ff);
            if(currentFilter!=NULL){
                cv::Mat temp(processedImg,faces[i]);
                currentFilter->setImage(temp);
                currentFilter->applyFilter();
                temp = currentFilter->getImage();
                temp.copyTo(processedImg(faces[i]));
            }
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
    //appendLog(QString::number(medianBlurSize)+QString(" to ")+QString::number(val));
    if(val%2==0){
        val++;
        medianBlurSizeSlider->setValue(val);
    }
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
    QVBoxLayout *boxLayout = new QVBoxLayout();
    QFormLayout *fLayout = new QFormLayout();
    filterPropWidget = currentFilter->getWidget();
    fLayout->addRow(QString("blur Size"),medianBlurSizeSlider);
    fLayout->addRow(QString("rect threshold"),rectThresholdSpinBox);
    fLayout->addRow(QString("Filter Type"),filterTypeComboBox);
    //fLayout->addRow(QString("Filter Properites"),filterPropWidget);
    boxLayout->addLayout(fLayout);
    stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(new QWidget());
    stackedLayout->addWidget(morphFilter->getWidget());
    stackedLayout->addWidget(sharpnessFilter->getWidget());
    stackedLayout->addWidget(dotPatternFilter->getWidget());
    //boxLayout->addLayout(filterPropBox);
    stackedLayout->setCurrentIndex(0);
    boxLayout->addLayout(stackedLayout);
    propertyWidget->setLayout(boxLayout);
}

void FaceDetector::updateFilterProperties(int i){
    //filterPropBox = new QVBoxLayout();
//    if(currentFilter!=NULL)
//        filterPropWidget=currentFilter->getWidget();
    stackedLayout->setCurrentIndex(i);
    somethingChanged();
}

bool FaceDetector::isChanged() const
{
    return changed;
}

void FaceDetector::setChanged(bool value)
{
    changed = value;
}


