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
    cv::Mat getImage();
    void applyFilter();

    bool isChanged() const;
    void setChanged(bool value);

public slots:
    void updateMorphElement(int elementType);
    void updateKernelSize(int kSize);
    void updateMorphOperation(int morphOpType);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void somethingChanged();

signals:

private:
    int element;
    int kSize;
    int morphOperationType;
    bool changed;
    cv::Mat tempImage;
    QSpinBox *kSizeSpinBox;
    QComboBox *morphTypeComboBox;
    QComboBox *morphElementComboBox;

    void createPropertyWidget();
    void createProperties();
};

#endif // MORPHOPERATIONS_H
