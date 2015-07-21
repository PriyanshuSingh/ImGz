#ifndef FILTER_H
#define FILTER_H

#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include <QDockWidget>
#include <QWidget>
#include <QPlainTextEdit>
class Filter:public QObject
{
    Q_OBJECT

public:
    Filter();
    virtual cv::Mat getImage(){ };
    virtual void applyFilter(){ };
    QWidget *getWidget();
    cv::Mat originalImg;
    cv::Mat processedImg;
    QWidget *propertyWidget;
    void setImage(cv::Mat im);
    void appendLog(QString message);
    void setLogText(QPlainTextEdit *logTxt);

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
    QPlainTextEdit *logTxt;
};

#endif // FILTER_H
