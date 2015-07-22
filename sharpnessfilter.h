#ifndef SHARPNESSFILTER_H
#define SHARPNESSFILTER_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include "filter.h"
#include <QSpinBox>
#include <QComboBox>


class SharpnessFilter : public Filter
{
    Q_OBJECT
public:
    SharpnessFilter();
    cv::Mat getImage();
    void applyFilter();

    bool isChanged() const;
    void setChanged(bool value);

public slots:
    void updateSharpType(int shartType);
    void mousePressed(QMouseEvent *ev);
    void mouseReleased(QMouseEvent *ev);
    void mouseMoved(QMouseEvent *ev);
    void somethingChanged();

signals:
    //void imageChanged();
private:
    int sharpType;
    bool changed;
    cv::Mat tempImage;
    //cv::Mat tempOriginalImg;
    cv::Mat kernal;
    QComboBox *sharpTypeComboBox;
    bool noneType;

    void createPropertyWidget();
    void createProperties();
};

#endif // SHARPNESSFILTER_H
