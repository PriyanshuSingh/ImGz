#ifndef CIRCLEDETECTORFILTER_H
#define CIRCLEDETECTORFILTER_H

#include <opencv2/core/core.hpp>
#include <vector>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include "filter.h"

class CircleDetectorFilter : public Filter
{

    Q_OBJECT

public:
    CircleDetectorFilter();

    bool isChanged() const;
    void setChanged(bool value);
    void applyFilter();
    void initPropertiesValues();
    cv::Mat getImage();

public slots:
    void somethingChanged();
    void handleImageChanged();
    void updateUpperThreshold(int thresh);
    void updateLowerThreshold(int thresh);
    void mouseMoved(QMouseEvent *ev);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);

private:
    cv::Mat grayImgMat;
    bool changed;
    int upperThreshold;
    int lowerThreshold;
    QSlider *lowerThresholdSlider;
    QSlider *upperThresholdSlider;
    std::vector< cv::Vec3f > circles;
    void createPropertyWidget();

};

#endif // CIRCLEDETECTORFILTER_H
