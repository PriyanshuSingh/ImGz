#ifndef FILTER_H
#define FILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
class Filter
{
public:
    Filter();
    virtual void mouseReleased(QMouseEvent *ev) { };
    virtual void mousePressed(QMouseEvent *ev) { };
    virtual void mouseMoved(QMouseEvent *ev) { };

    cv::Mat originalImg;
    cv::Mat processedImg;
    virtual cv::Mat getImage(){ };
    QWidget *propertyWidget;
    void setImage(cv::Mat im);

protected:
    void setProcessed(bool proc);
    bool isProcessed();

private:
    bool imageReady;
};

#endif // FILTER_H
