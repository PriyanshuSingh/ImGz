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
    virtual cv::Mat getImage(){ };
    virtual void applyFilter(){ };
    QWidget *getWidget();
    cv::Mat originalImg;
    cv::Mat processedImg;
    QWidget *propertyWidget;
    void setImage(cv::Mat im);

signals:
    void imageChanged();

public slots:
    virtual void mouseReleased(QMouseEvent *ev) { };
    virtual void mousePressed(QMouseEvent *ev) { };
    virtual void mouseMoved(QMouseEvent *ev) { };

protected:
    void setProcessed(bool proc);
    bool isProcessed();

private:
    bool imageReady;
};

#endif // FILTER_H
