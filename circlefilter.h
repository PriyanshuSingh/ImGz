#ifndef CIRCLEFILTER_H
#define CIRCLEFILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include "filter.h"
class QPoint;

class CircleFilter : public Filter
{
public:
    CircleFilter();
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    cv::Mat getImage();
private:
    bool centerDefined;
    bool radiusDefined;
    bool okToContiue;
    QPoint center;
    int radius;
    cv::Mat tempImg;
};

#endif // CIRCLEFILTER_H
