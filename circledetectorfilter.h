#ifndef CIRCLEDETECTORFILTER_H
#define CIRCLEDETECTORFILTER_H

#include <opencv2/core/core.hpp>
#include <vector>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include "filter.h"

class CircleDetectorFilter : public Filter
{

    Q_OBJECT

public:
    CircleDetectorFilter();

    bool isChanged() const;
    void setChanged(bool value);
    void applyFilter();
    void mouseMoved(QMouseEvent *ev);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    cv::Mat getImage();

public slots:
    void somethingChanged();
    void handleImageChanged();

private:
    cv::Mat grayImgMat;
    bool changed;
    std::vector< cv::Vec3f > circles;
};

#endif // CIRCLEDETECTORFILTER_H
