#ifndef MORPHOPERATIONS_H
#define MORPHOPERATIONS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "filter.h"
#include <QSpinBox>
#include <QComboBox>

class MorphOperations : public Filter
{
    Q_OBJECT
public: 
    MorphOperations();
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void updateBottomDock(QDockWidget *dock, QWidget *parent);
    cv::Mat getImage();
    void applyFilter();
public slots:
    void updateMorphElement(int elementType);
    void updateKernelSize(int kSize);
    void updateMorphOperation(int morphOpType);

signals:

private:
    int element;
    int kSize;
    int morphOperationType;
    cv::Mat tempImage;
    QSpinBox *kSizeSpinBox;
    QComboBox *morphTypeComboBox;
    QComboBox *morphElementComboBox;
};

#endif // MORPHOPERATIONS_H
