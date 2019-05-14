#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cameraScene = new QGraphicsScene(this);
    dataScene = new QGraphicsScene(this);


    ui->graphicsView_Data->setScene(dataScene);
    ui->graphicsView_CameraRaw->setScene(cameraScene);
    GraphicBot *b = new GraphicBot();
    dataScene->addItem(b);
    b->setRotation(270);


}

MainWindow::~MainWindow()
{
    delete ui;
}
