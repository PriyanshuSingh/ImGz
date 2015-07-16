#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
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

private:
    //Main Widget
    RasterLabel *rasterLabel;

    //Action
    QAction *circleAction;

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
    void createMenu();
    void createToolBar();
    void createStatusBar();
    void createDockWidget();
    void createBottomDock();


    Filter *ceff;


    cv::Mat ii;
};

#endif // MAINWINDOW_H
