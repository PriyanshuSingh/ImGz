#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include "morphOperations.h"
#include "circlefilter.h"

class Filter;
class CircleFilter;
class RasterLabel;
class QPlainTextEdit;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:

private slots:
    void open();
    void updateStatusBar(QMouseEvent*);
    void enableCircleFilter();
    void enableMorphFilter();
    void enableWebcam();

private:
    //Main Widget
    RasterLabel *rasterLabel;

    //Action
    QAction *circleAction;
    QAction *morphAction;

    QAction *openAction;
    QAction *saveAction;
    QAction *aboutAction;
    QAction *openWebcamAction;

    //Menu
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *effectMenu;


    //DockWidgets
    QDockWidget *bottomDock;
    QDockWidget *rightDock;

    QPlainTextEdit *logTxtEdit;

    QToolBar *leftToolBar;

    QLabel *xyLabel;

    //create function
    void createAction();
    void createMenu();
    void createToolBar();
    void createStatusBar();
    void createDockWidget();
    void createFilter();
    void updateDock();

    Filter *currentFilter;

    CircleFilter *circleFitler;
    MorphOperations *morphFilter;

    cv::Mat mainImage;
    QString filePath;

};

#endif // MAINWINDOW_H
