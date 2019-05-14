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
    ui->graphicsView_data_large->setScene(dataScene);
    ui->graphicsView_CameraRaw->setScene(cameraScene);
    RobotLocation *b = new RobotLocation();
    dataScene->addItem(b);
    dataScene->addRect(0,0,globalSettings.fieldSizeX,globalSettings.fieldSizeY);

    for(int i =0;i<10000;i++){
        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;
        int a = qrand() % 360;
        RobotLocation *l = new RobotLocation();
        l->x = x;
        l->y = y;
        l->setX(x-0.5*globalSettings.botDiameter);
        l->setY(y-0.5*globalSettings.botDiameter);
        l->setRotation(a);
        dataScene->addItem(l);

    }
    //ui->graphicsView_Data->fitInView(dataScene->sceneRect(), Qt::KeepAspectRatio);
    update();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int width = globalSettings.fieldSizeX;
    int height = globalSettings.fieldSizeY;
    //ui->graphicsView_Data->setFixedSize(width, height);
    ui->graphicsView_Data->setSceneRect(0-10, 0-10, width+10, height+10);
    ui->graphicsView_Data->fitInView(0-10, 0-10, width+10, height+10, Qt::KeepAspectRatio);
    ui->graphicsView_data_large->setSceneRect(0-10, 0-10, width+10, height+10);
    ui->graphicsView_data_large->fitInView(0-10, 0-10, width+10, height+10, Qt::KeepAspectRatio);
    repaint();

}
