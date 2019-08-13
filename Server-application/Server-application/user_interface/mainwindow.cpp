#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
     * Only uncomment this peace of code to check if opencv works correctly within QT
     */
        // read an image
//        cv::Mat image = cv::imread("", 1);
//        // create image window named "My Image"
//        cv::namedWindow("My Image");
//        // show the image on window
//        cv::imshow("My Image", image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
