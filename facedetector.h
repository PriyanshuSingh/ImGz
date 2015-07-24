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
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filter.h"
#include "circlefilter.h"
#include "morphOperations.h"
#include "dotpatternfilter.h"
#include "sharpnessfilter.h"

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

private:
    bool changed;

    Filter *currentFilter;

    MorphOperations *morphFilter;
    DotPatternFilter *dotPatternFilter;
    SharpnessFilter *sharpnessFilter;

    cv::Mat grayImgMat;
    cv::CascadeClassifier frontalFaceCascade;
    cv::CascadeClassifier profileFaceCascade;

    QSlider *medianBlurSizeSlider;
    QSpinBox *rectThresholdSpinBox;

    int rectThreshold;
    int medianBlurSize;

    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> tempfaces;

    void createPropertyWidget();
};

#endif // FACEDETECTOR_H
