#ifndef CIRCLEFILTER_H
#define CIRCLEFILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include "filter.h"
class QPoint;

class CircleFilter : public Filter
{
    Q_OBJECT
public:
    CircleFilter();
    cv::Mat getImage();
    void applyFilter();

    bool isNewCircleInProgress() const;
    void setNewCircleInProgress(bool value);
    void initPropertiesValues();

public slots:
    void updateThickness(int i);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void setFilledCircle(bool value);

signals:

private:
    bool newCircleInProgress;
    QPoint center;
    int radius;
    int thickness;
    cv::Mat tempImg;
    QSpinBox *thicknessSpinBox;
    QCheckBox *filledCheckBox;
    void createPropertyWidget();
};

#endif // CIRCLEFILTER_H
