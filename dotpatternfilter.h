#ifndef DOTPATTERNFILTER_H
#define DOTPATTERNFILTER_H

#include <QObject>
#include "filter.h"
#include <opencv2/core/core.hpp>
class DotPatternFilter : public Filter
{

    Q_OBJECT

public:
    DotPatternFilter();

    void applyFilter();
    void mouseMoved(QMouseEvent *ev);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    cv::Mat getImage();

    void createPatternMask();
    void createPixelattedImage();

    bool isChanged() const;
    void setChanged(bool value);


public slots:
    void somethingChanged();
    void handleImageChanged();

private:
    bool changed;
    int squareSize;
    cv::Mat destMat;
    cv::Mat patternMaskMat;
    cv::Mat destMat_32f;
};

#endif // DOTPATTERNFILTER_H
