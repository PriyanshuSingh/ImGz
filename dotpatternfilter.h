#ifndef DOTPATTERNFILTER_H
#define DOTPATTERNFILTER_H

#include <QObject>
#include "filter.h"
#include <opencv2/core/core.hpp>
#include <QSlider>
#include <QCheckBox>
class DotPatternFilter : public Filter
{

    Q_OBJECT

public:
    DotPatternFilter();

    void applyFilter();
    cv::Mat getImage();
    void initPropertiesValues();
    void createPatternMask();
    void createPixelattedImage();

    bool isChanged() const;
    void setChanged(bool value);


    bool isFilled() const;


public slots:
    void mouseMoved(QMouseEvent *ev);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void somethingChanged();
    void handleImageChanged();
    void updateSquareSize(int sq);
    void setFilled(bool value);

private:
    bool changed;
    bool filled;
    int squareSize;
    QSlider *squareSizeSlider;
    QCheckBox *filledCheckBox;
    cv::Mat destMat;
    cv::Mat patternMaskMat;
    cv::Mat destMat_32f;

    void createPropertyWidget();
};

#endif // DOTPATTERNFILTER_H
