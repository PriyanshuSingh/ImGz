#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H
#include <QStackedLayout>
#include <QComboBox>
#include <opencv2/core/core.hpp>
#include <vector>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include<QVBoxLayout>
#include<QFormLayout>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "filter.h"
#include <QObject>
#include <QWidget>
#include "opencv2/core/core.hpp"
//#include "opencv2/contrib/contrib.hpp"
//#include "opencv2/face.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <QCheckBox>
#include <iostream>
#include <fstream>
#include <sstream>

class FaceRecognition : public Filter
{
    Q_OBJECT
public:
    FaceRecognition();
    virtual cv::Mat getImage(){return this->processedImg;}
    virtual void applyFilter(){}
    virtual void initPropertiesValues(){}

    bool isChanged() const;
    void setChanged(bool value);
    cv::Mat correctGamma( cv::Mat& img, double gamma );
    cv::Mat correctSharpness(cv::Mat& img);
    cv::Mat applyHistEq(cv::Mat& img);
    static int read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
public slots:
    virtual void mouseReleased(QMouseEvent *ev){}
    virtual void mousePressed(QMouseEvent *ev){}
    virtual void mouseMoved(QMouseEvent *ev){}
    void handleImageChanged(){}
    void somethingChanged(){}
    void updateFaceRecAlgo(int){}
    void updateGamma(int){}
    void updateHistEqStatus(bool){}
    void updateSharpnessStatus(bool){}

private:
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    QComboBox *faceRecAlgoComboBox;
    QSlider *gammaSlider;
    QCheckBox *histEqCheckBox;
    QCheckBox *sharpnessCheckBox;
    cv::Ptr<cv::FeatureDetector>/*face::FaceRecognizer*/ currentAlgo;
    cv::CascadeClassifier haar_cascade;
    cv::Mat grayImgMat;
    bool histEqStatus;
    double gamma;
    bool sharpnessStatus;
};

#endif // FACERECOGNITION_H
