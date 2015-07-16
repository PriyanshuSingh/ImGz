#ifndef CIRCLEFILTER_H
#define CIRCLEFILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include "filter.h"
class QPoint;

class CircleFilter : public Filter
{
    Q_OBJECT
public:
    CircleFilter();
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void updateBottomDock(QDockWidget *dock, QWidget *parent);
    cv::Mat getImage();

public slots:
    void updateThickness(int i);

signals:

private:
    bool centerDefined;
    bool radiusDefined;
    bool okToContiue;
    QPoint center;
    int radius;
    int thickness;
    cv::Mat tempImg;
    QSpinBox *thickn;
};

#endif // CIRCLEFILTER_H
