#ifndef RECTANGLEFILTER_H
#define RECTANGLEFILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include "filter.h"

class RectangleFilter : public Filter
{
    Q_OBJECT

public:
    RectangleFilter();

    cv::Mat getImage();
    void applyFilter();

    bool isNewRectangleInProgress() const;
    void setNewRectangleInProgress(bool value);

public slots:
    void updateThickness(int i);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void setFilledRectangle(bool val);

private:
    bool newRectangleInProgress;
    QPoint pt1;
    QPoint pt2;

    int thickness;
    QSpinBox *thicknessSpinBox;
    QCheckBox *filledCheckBox;
    void createPropertyWidget();
};

#endif // RECTANGLEFILTER_H
