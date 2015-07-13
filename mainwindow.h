#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void processFrameAndUpdateGui();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capWebcam;
    cv::Mat matOriginal;
    cv::Mat matProcessed;

    int currentFilter;

    QImage qimgOriginal;
    QImage qimgProcessed;

    std::vector< cv::Vec3f > vecCircles;
    std::vector< cv::Vec3f >::iterator itrCircles;

    QTimer* tmrTimer;
    /////////////////////////////////////////////////////
    /// \brief fillComboBoxWithFilters
    /// we will use MODELS for comboBox items.
    /// initializing comboBox values through a hack for
    /// testing purposes
    void fillComboBoxWithFilters();
    static const int COMBO_BOX_LENGTH = 4;
    static const int ORIGINAL = 0;
    static const int GAUSSIAN_BLUR = 1;
    static const int BOX_BLUR = 2;
    static const int CANNY_EDGES = 3;
    /////////////////////////////////////////////////////
};

#endif // MAINWINDOW_H
