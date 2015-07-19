#ifndef OPENINGFILTER_H
#define OPENINGFILTER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "filter.h"
#include <QSpinBox>
#include <QComboBox>

class OpeningFilter : public Filter
{
    Q_OBJECT
public: 
    OpeningFilter();
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void updateBottomDock(QDockWidget *dock, QWidget *parent);
    cv::Mat getImage();
    void applyFilter();
public slots:
    void updateMorphElement(int elementType);
    void updateKernelSize(int kSize);

signals:

private:
    int element;
    int kSize;
    cv::Mat tempImage;
    QSpinBox *kernelSize;
    QComboBox *morphElement;
};

#endif // OPENINGFILTER_H
