#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


QGraphicsScene *dataScene;   //global


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //cameraScene = new QGraphicsScene(this);
    dataScene = new QGraphicsScene(this);


    ui->graphicsView_Data->setScene(dataScene);
    ui->graphicsView_data_large->setScene(dataScene);
//    ui->graphicsView_CameraRaw->setScene(cameraScene);
//    ui->graphicsView_CameraRaw_large->setScene(cameraScene);
    dataScene->addRect(0,0,globalSettings.fieldSizeX,globalSettings.fieldSizeY);


    for(int i =0;i<8;i++){

        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;
        int a = qrand() % 360;

        RobotLocation *l = robotLocationManager.addSimulatedRobot();
        l->x = x;
        l->y = y;
        l->setX(x-0.5*globalSettings.botDiameter);
        l->setY(y-0.5*globalSettings.botDiameter);
        l->destinationX = x;
        l->destinationY = y;
        l->setRotation(a);
        dataScene->addItem(l);
    }
    //dataScene->addItem(&algorithmVisualisation);
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

void MainWindow::updateGui()
{
    int t = fpsTimer->elapsed();
    fpsTimer->restart();
    int fps = (double)1000.0/(double)t;
    ui->fpsNumber->display(fps);

    qDebug() << "update Gui called" << endl;
    QImage img((uchar*)robotDetectionSettings.processedFrame.data, robotDetectionSettings.processedFrame.cols, robotDetectionSettings.processedFrame.rows, QImage::Format_RGB888);

    QPixmap p = QPixmap::fromImage(img);
    int w = ui->cameraFeedLabel->width();
    int h = ui->cameraFeedLabel->height();
    int wl = ui->cameraFeedLabel_Large->width()-1;   //else it will keep expanding ????
    int hl = ui->cameraFeedLabel_Large->height()-1;  //else it will keep expanding ????

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->cameraFeedLabel->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->cameraFeedLabel_Large->setPixmap(p.scaled(wl,hl,Qt::KeepAspectRatio));
    on_pushButton_clicked(); // resize the scenes



    dataScene->update();
}
void MainWindow::colorSlidersChanged(int c)
{

    if(flipFlop){
        int currentColor = ui->colorComboBox->currentIndex();
        int h = ui->sliderHue->value();
        int s = ui->sliderSaturation->value();
        int v = ui->sliderVDinges->value();

        robotDetectionSettings.HSVColorValues.at(currentColor)->h = h;
        robotDetectionSettings.HSVColorValues.at(currentColor)->s = s;
        robotDetectionSettings.HSVColorValues.at(currentColor)->v = v;
    }


}

void MainWindow::on_colorComboBox_currentIndexChanged(int index)
{
    //update new sliders
    qDebug() << "comboBox index: " << index;
    flipFlop = false;
    ui->sliderHue->setValue(robotDetectionSettings.HSVColorValues.at(index)->h);
    ui->sliderSaturation->setValue(robotDetectionSettings.HSVColorValues.at(index)->s);
    ui->sliderVDinges->setValue(robotDetectionSettings.HSVColorValues.at(index)->v);
    flipFlop = true;

}

void MainWindow::on_sliderDilate_valueChanged(int value)
{
    robotDetectionSettings.dilateObject = value;
}


void MainWindow::on_sliderDeviation_valueChanged(int value)
{
    robotDetectionSettings.xyDeviationMilimeter = value;
}

void MainWindow::on_sliderErode_valueChanged(int value)
{
    robotDetectionSettings.erodeObject = value;
}
