#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <opencv2/core/core.hpp>
#include <vector>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include<QVBoxLayout>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filter.h"
#include "circlefilter.h"
#include "morphOperations.h"
#include "dotpatternfilter.h"
#include "sharpnessfilter.h"
#include <QComboBox>

class FaceDetector : public Filter
{
    Q_OBJECT

public:
    FaceDetector();
    virtual cv::Mat getImage();
    virtual void applyFilter();
    virtual void initPropertiesValues();

    bool isChanged() const;
    void setChanged(bool value);


public slots:
    virtual void mouseReleased(QMouseEvent *ev);
    virtual void mousePressed(QMouseEvent *ev);
    virtual void mouseMoved(QMouseEvent *ev);
    void handleImageChanged();
    void somethingChanged();
    void updateMedianBlurSizeSlider(int);
    void updateRectThresholdSpinBox(int);
    void updateFilterType(int i);

private:
    bool changed;


    Filter *currentFilter;
    MorphOperations *morphFilter;
    DotPatternFilter *dotPatternFilter;
    SharpnessFilter *sharpnessFilter;
    //int frameCount;

    cv::Mat grayImgMat;
    cv::CascadeClassifier frontalFaceCascade;
    cv::CascadeClassifier profileFaceCascade;

    QSlider *medianBlurSizeSlider;
    QSpinBox *rectThresholdSpinBox;
    QComboBox *filterTypeComboBox;
    QWidget *filterPropWidget;


    int rectThreshold;
    int medianBlurSize;

    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> tempfaces;

    void createPropertyWidget();
    void updateFilterProperties();
};

#endif // FACEDETECTOR_H
