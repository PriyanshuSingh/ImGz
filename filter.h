#ifndef FILTER_H
#define FILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include <QDockWidget>
#include<QWidget>
class Filter:public QObject
{
public:
    Filter();
    virtual void mouseReleased(QMouseEvent *ev) { };
    virtual void mousePressed(QMouseEvent *ev) { };
    virtual void mouseMoved(QMouseEvent *ev) { };
    virtual void updateBottomDock(QDockWidget *dock, QWidget *parent){ };
    virtual cv::Mat getImage(){ };
    cv::Mat originalImg;
    cv::Mat processedImg;
    QWidget *propertyWidget;
    void setImage(cv::Mat im);

protected:
    void setProcessed(bool proc);
    bool isProcessed();

private:
    bool imageReady;
};

#endif // FILTER_H
