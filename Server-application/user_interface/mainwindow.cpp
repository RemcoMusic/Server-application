#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <simulatedrobot.h>


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


    fpsTimer = new QTime();
    fpsTimer->start();

    ui->fpsNumber->setPalette(Qt::red);
    ui->lcdNumberHue->setPalette(Qt::red);
    ui->lcdNumberSaturation->setPalette(Qt::red);
    ui->lcdNumberVDinges->setPalette(Qt::red);
    ui->lcdNumberErode->setPalette(Qt::green);
    ui->lcdNumberDilate->setPalette(Qt::green);
    ui->lcdNumberDeviation->setPalette(Qt::green);
    ui->lcdNumberTotalRobots->setPalette(Qt::red);
    ui->lcdNumberSimulatedRobots->setPalette(Qt::green);
    ui->lcdNumberRealRobots->setPalette(Qt::green);
    ui->lcdNumberTotalObstacles->setPalette(Qt::green);


    connect(ui->sliderHue, SIGNAL(valueChanged(int)),this, SLOT(colorSlidersChanged(int)));
    connect(ui->sliderSaturation, SIGNAL(valueChanged(int)),this, SLOT(colorSlidersChanged(int)));
    connect(ui->sliderVDinges, SIGNAL(valueChanged(int)),this, SLOT(colorSlidersChanged(int)));

    connect(ui->sliderHue, SIGNAL(valueChanged(int)),ui->lcdNumberHue, SLOT(display(int)));
    connect(ui->sliderSaturation, SIGNAL(valueChanged(int)),ui->lcdNumberSaturation, SLOT(display(int)));
    connect(ui->sliderVDinges, SIGNAL(valueChanged(int)),ui->lcdNumberVDinges, SLOT(display(int)));


    //on_colorComboBox_currentIndexChanged(0);
    ui->sliderErode->setValue(robotDetectionSettings.erodeObject);
    ui->sliderDilate->setValue(robotDetectionSettings.dilateObject);
    ui->sliderDeviation->setValue(robotDetectionSettings.xyDeviationMilimeter);


    for(int i =0;i<1;i++){
        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;
        int a = qrand() % 360;

        RobotLocation *l = locationManager.addSimulatedRobot();
        l->x = x;
        l->y = y;
        l->setX(x-0.5*globalSettings.botDiameter);
        l->setY(y-0.5*globalSettings.botDiameter);
        l->destinationX = x;
        l->destinationY = y;
        l->setRotation(a);
        l->simulatedRobot = new SimulatedRobot(l);
        dataScene->addItem(l->simulatedRobot);
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
double smoothFps=0;
void MainWindow::updateGui()
{

    if(firstTime){
        firstTime = false;
        for(int i = 0; i<swarmAlgorithmsSettings.anvailableAlgoritms.size();i++){
            ui->ActiveAlgoritmList->addItem(swarmAlgorithmsSettings.anvailableAlgoritms.at(i));
        }


    }
    int t = fpsTimer->elapsed();
    fpsTimer->restart();
    int fps = (double)1000.0/(double)t;
    smoothFps += 0.1*(fps-smoothFps);
    ui->fpsNumber->display((int)smoothFps);

    QImage img((uchar*)robotDetectionSettings.processedFrame.data, robotDetectionSettings.processedFrame.cols, robotDetectionSettings.processedFrame.rows, QImage::Format_RGB888);
    QPixmap p = QPixmap::fromImage(img);
    int w = ui->cameraFeedLabel->width();
    int h = ui->cameraFeedLabel->height();
    int wl = ui->cameraFeedLabel_Large->width()-1;   //else it will keep expanding ????
    int hl = ui->cameraFeedLabel_Large->height()-1;  //else it will keep expanding ????
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->cameraFeedLabel->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->cameraFeedLabel_Large->setPixmap(p.scaled(wl,hl,Qt::KeepAspectRatio));



    QImage imgr((uchar*)robotDetectionSettings.processedRedFrame.data, robotDetectionSettings.processedRedFrame.cols, robotDetectionSettings.processedRedFrame.rows, QImage::Format_RGB888);
    QPixmap pr = QPixmap::fromImage(imgr);
    int wr = ui->cameraRedFeed->width();
    int hr = ui->cameraRedFeed->height();
    ui->cameraRedFeed->setPixmap(pr.scaled(wr,hr,Qt::KeepAspectRatio));

    QImage imgg((uchar*)robotDetectionSettings.processedGreenFrame.data, robotDetectionSettings.processedGreenFrame.cols, robotDetectionSettings.processedGreenFrame.rows, QImage::Format_RGB888);
    QPixmap pg = QPixmap::fromImage(imgg);
    int wg = ui->cameraGreenFeed->width();
    int hg = ui->cameraGreenFeed->height();
    ui->cameraGreenFeed->setPixmap(pg.scaled(wg,hg,Qt::KeepAspectRatio));

    QImage imgb((uchar*)robotDetectionSettings.processedBlueFrame.data, robotDetectionSettings.processedBlueFrame.cols, robotDetectionSettings.processedBlueFrame.rows, QImage::Format_RGB888);
    QPixmap pb = QPixmap::fromImage(imgb);
    int wb = ui->cameraBlueFeed->width();
    int hb = ui->cameraBlueFeed->height();
    ui->cameraBlueFeed->setPixmap(pb.scaled(wb,hb,Qt::KeepAspectRatio));


    updateNumberOfRobots();

    on_pushButton_clicked(); // resize the scenes
    dataScene->update();
}

void MainWindow::updateNumberOfRobots()
{
    int real = 0;
    int sim = 0;
    for(int i = 0; i < locationManager.robots.size();i++){
        if(locationManager.robots.at(i)->type == Object::Type::REAL){
            real++;
        }else{
            sim++;
        }
    }
    ui->lcdNumberTotalRobots->display(real+sim);
    ui->lcdNumberSimulatedRobots->display(sim);
    ui->lcdNumberRealRobots->display(real);
    ui->lcdNumberTotalObstacles->display(locationManager.objects.size());
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

void MainWindow::on_checkRealSimulation_stateChanged(int arg1)
{
    qDebug() << arg1;
    swarmSimulationSettings.realisticSimulationEnabled = arg1;
}

void MainWindow::on_checkAccelerationControl_stateChanged(int arg1)
{
    swarmSimulationSettings.acceleartionControlEnabled = arg1;
}

void MainWindow::on_checkInconsisentMotors_stateChanged(int arg1)
{
    swarmSimulationSettings.badMotorsEnbabled = arg1;
}

void MainWindow::on_checkUADWLB_stateChanged(int arg1)
{
    swarmAlgorithmsSettings.useAllDestinationsWhenLessRobots = arg1;
}

void MainWindow::on_checkDynamicSpeed_stateChanged(int arg1)
{
    swarmAlgorithmsSettings.dynamicSpeed = arg1;
}

void MainWindow::on_checkRotationTime_stateChanged(int arg1)
{
    swarmAlgorithmsSettings.useLineAlgorithmRotationTime = arg1;
}

void MainWindow::on_SliderRobotSpeed_valueChanged(int value)
{
    swarmAlgorithmsSettings.robotSpeed = value;
}

void MainWindow::on_AddSimulatedRobotButton_clicked()
{
    //for(int i =0;i<10;i++){
        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;
        int a = qrand() % 360;

        RobotLocation *l = locationManager.addSimulatedRobot();
        l->x = x;
        l->y = y;
        l->setX(x-0.5*globalSettings.botDiameter);
        l->setY(y-0.5*globalSettings.botDiameter);
        l->destinationX = x;
        l->destinationY = y;
        l->setRotation(a);
        l->simulatedRobot = new SimulatedRobot(l);
        dataScene->addItem(l->simulatedRobot);
        dataScene->addItem(l);
    //}
}

void MainWindow::on_addSimulatedObjectButton_clicked()
{
    int x = qrand() % globalSettings.fieldSizeX;
     int y = qrand() % globalSettings.fieldSizeY;

     Ball *b = new Ball();
     b->x = x;
     b->y = y;
     dataScene->addItem(b);
     locationManager.addObject(b);
}

void MainWindow::on_ActiveAlgoritmList_currentIndexChanged(const QString &arg1)
{
    swarmAlgorithmsSettings.runNewAlgortim(arg1);
}

void MainWindow::on_resetSimulationButton_clicked()
{
    //turn off all robots.
    communicationSettings.turnOffAllRobots();  // will also reset IP list

    //clear qgraphicsscene
    dataScene->clear();
    for(int i =locationManager.robots.size()-1; i>=0 ;i--){
        locationManager.robots.removeAt(i);
    }
    //remove all robots in the robotLocation
    //locationManager.robots.clear();
    //reset IP list tracker


    //add fieldsize back
    dataScene->addRect(0,0,globalSettings.fieldSizeX,globalSettings.fieldSizeY);

}
