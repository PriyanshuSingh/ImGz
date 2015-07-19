#ifndef RASTERLABEL_H
#define RASTERLABEL_H

#include <QObject>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include "filter.h"
#include <QTimer>

class RasterLabel : public QLabel
{
    Q_OBJECT

public:
    RasterLabel(QWidget *parent = 0);
    ~RasterLabel();

    void setFilter(Filter *filter);
    void setImage(cv::Mat img);

    bool isFilterDefined() const;
    bool isImgDefined() const;

signals:
    void nothingToDisplay();
    void mouseMoved(QMouseEvent *ev);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);

public slots:
    void renderImage();

private slots:
    void noDisplayableImage();

private:
    cv::Mat imgMat;

    Filter *filter;
    QImage qimg;
    QTimer *tmr;
    bool filterDefined;
    bool imgDefined;
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // RASTERLABEL_H
