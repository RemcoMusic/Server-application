#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <chargealgorithm.h>
#include <chargestation.h>
#include <elasticball.h>


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
        locationManager.addSimulatedRobot();
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

    QImage imgo((uchar*)robotDetectionSettings.processedOrangeFrame.data, robotDetectionSettings.processedOrangeFrame.cols, robotDetectionSettings.processedOrangeFrame.rows, QImage::Format_RGB888);
    QPixmap po = QPixmap::fromImage(imgo);
    int wo = ui->cameraObjectFeed->width();
    int ho = ui->cameraObjectFeed->height();
    ui->cameraObjectFeed->setPixmap(po.scaled(wo,ho,Qt::KeepAspectRatio));

    updateNumberOfRobots();
    removeUnusedRobots();
    updateManualControl();
    updateRobotStatusLabel();
    on_pushButton_clicked(); // resize the scenes
    loadCameraSelection();
    dataScene->update();
}
void MainWindow::updateRobotStatusLabel(){
    RobotLocation *ptr = nullptr;
    if(!LocationManager::currentSelectedObjects.isEmpty())
    {
        ptr = dynamic_cast<RobotLocation*>(LocationManager::currentSelectedObjects.last());
    }
    if(ptr){
        //location
        QString locationText = "X:";
        locationText.append(QString::number(ptr->x));
        locationText.append(" Y:");
        locationText.append(QString::number(ptr->y));
        ui->robotLocationLabel->setText(locationText);

        //destination
        QString destination = "X:";
        destination.append(QString::number(ptr->destinationX));
        destination.append(" Y:");
        destination.append(QString::number(ptr->destinationY));
        ui->robotDestinationLabel->setText(destination);

        //angle
        ui->robotAngleLabel->setText(QString::number(ptr->angle*57,10,1));

        //ip
        ui->robotIPLabel->setText(ptr->ip);

        //type
        if(ptr->type == RobotLocation::Type::REAL){
            ui->robotTypeLabel->setText("Real");
        }else{ // simulated
            ui->robotTypeLabel->setText("Simulated");
        }

        //voltage
        ui->robotVoltageLabel->setText(QString::number(ptr->batteryVoltage,10,2));

        if(ptr->group){
            ui->robotGroupLabel->setText(ptr->group->name);
        }else{
            ui->robotGroupLabel->setText("Default");
        }

        ui->deleteSelected->setEnabled(true);
        ui->emptyBattery->setEnabled(true);
    }
    else {
        //location
        ui->robotLocationLabel->setText("");

        //destination
        ui->robotDestinationLabel->setText("");

        //angle
        ui->robotAngleLabel->setText("");

        //ip
        ui->robotIPLabel->setText("");

        //type
        ui->robotTypeLabel->setText("");

        //voltage
        ui->robotVoltageLabel->setText("");

        ui->robotGroupLabel->setText("");

        ui->deleteSelected->setEnabled(false);
        ui->emptyBattery->setEnabled(false);
    }

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

void MainWindow::removeUnusedRobots()
{
    for(int i = 0; i < locationManager.robots.size();i++){
        RobotLocation * ptr = locationManager.robots.at(i);
        if(ptr->sharedData.status == robotStatus::STARTUP){
            //now delete ptr
            //int index = locationManager.robots.indexOf(ptr);

            locationManager.robots.removeOne(ptr);
            dataScene->removeItem(ptr->simulatedRobot);
            dataScene->removeItem(ptr);

             // delete ptr;
        }
    }
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
void MainWindow::on_SimulationSpeedSlider_valueChanged(int value)
{
    swarmSimulationSettings.simulationSpeed = value;
}

void MainWindow::on_AddSimulatedRobotButton_clicked()
{
    locationManager.addSimulatedRobot();
}



void MainWindow::on_ActiveAlgoritmList_currentIndexChanged(const QString &arg1)
{
    swarmAlgorithmsSettings.runNewAlgortim(arg1);
}

void MainWindow::on_resetSimulationButton_clicked()
{
    locationManager.resetEverything();
}

void MainWindow::on_algorithmInputComboBox_currentIndexChanged(int index)
{
    swarmAlgorithmsSettings.inputSource = (SwarmAlgorithmsSettings::AlgorithmInputSource)index;
}

//for manual control
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)wPressed = true;
    else if(event->key() == Qt::Key_S)sPressed = true;
    else if(event->key() == Qt::Key_A)aPressed = true;
    else if(event->key() == Qt::Key_D)dPressed = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)wPressed = false;
    else if(event->key() == Qt::Key_S)sPressed = false;
    else if(event->key() == Qt::Key_A)aPressed = false;
    else if(event->key() == Qt::Key_D)dPressed = false;
}
void MainWindow::updateManualControl()
{

    for(int i = 0;i < LocationManager::currentSelectedObjects.size(); i++)
    {
        RobotLocation *robot = dynamic_cast<RobotLocation*>(LocationManager::currentSelectedObjects.at(i));
        Object *object = LocationManager::currentSelectedObjects.at(i);

        if(robot)//if the selected object is a robot
        {
            int speed = 0;//  mm/frame
            double angle = robot->angle;
            if(wPressed)
            {
                speed = 100;
            }
            if(sPressed)
            {
                speed = 100;
            }
            if(aPressed)
            {
                angle -= 0.2 * M_PI;
            }
            if(dPressed)
            {
                angle += 0.2 * M_PI;
            }
            if(wPressed || sPressed || aPressed || dPressed)
            {
                while(angle >= 2*M_PI) angle-=2 * M_PI;
                while(angle < 0) angle += 2 * M_PI;
                robot->destinationX = robot->x + cos(angle) * speed;
                robot->destinationY = robot->y + sin(angle) * speed;
                robot->endAngle = angle;
                robot->speed = swarmAlgorithmsSettings.robotSpeed;
            }
        }
        else if(object)
        {
            if(wPressed)
            {
                object->y -= 10;
            }
            if(sPressed)
            {
                object->y += 10;
            }
            if(aPressed)
            {
                object->x -= 10;
            }
            if(dPressed)
            {
                object->x += 10;
            }
        }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)  // sorry for the horrible name
{
    if(arg1 == "Charge Station"){
        int x = 0.5 * globalSettings.fieldSizeX;
        int y = 0.5 * globalSettings.fieldSizeY;

         ChargeStation* b = new ChargeStation();
         b->x = x;
         b->y = y;
         b->type = Object::Type::SIMULATED;
         locationManager.addObject(b);
    }else if (arg1 == "Simulated Ball Yellow") {
        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;

         Ball* b = new Ball();
         b->x = x;
         b->y = y;
         b->BallColor = Ball::BallColor::YELLOW;
         b->type = Object::Type::SIMULATED;
         locationManager.addObject(b);
    }else if (arg1 == "Simulated Ball Orange") {
        int x = qrand() % globalSettings.fieldSizeX;
        int y = qrand() % globalSettings.fieldSizeY;

         Ball* b = new Ball();
         b->x = x;
         b->y = y;
         b->BallColor = Ball::BallColor::ORANGE;
         b->type = Object::Type::SIMULATED;
         locationManager.addObject(b);
    }
    else if (arg1 == "Simulated Elastic Ball") {
            int x = qrand() % globalSettings.fieldSizeX;
            int y = qrand() % globalSettings.fieldSizeY;

             Ball* b = new ElasticBall();
             b->x = x;
             b->y = y;
             b->type = Object::Type::SIMULATED;
             locationManager.addObject(b);
        }
    ui->comboBox->setCurrentIndex(0);
}


void MainWindow::on_deleteSelected_clicked()
{
    while(LocationManager::currentSelectedObjects.size() > 0){
        Object* toDelete = LocationManager::currentSelectedObjects.takeAt(0);

        RobotLocation *robot = dynamic_cast<RobotLocation*>(toDelete);
        if(robot)
        {
            locationManager.robots.removeOne(robot);
        }
        dataScene->removeItem(toDelete);
        delete toDelete;
    }
}

void MainWindow::on_emptyBattery_clicked()
{
    for(int i = 0;i < LocationManager::currentSelectedObjects.size(); i++)
    {
        //check if this object is a robot object
        RobotLocation *robot = dynamic_cast<RobotLocation*>(LocationManager::currentSelectedObjects.at(i));
        if(robot)
        {
            QListIterator<SwarmAlgorithmBase*> i = swarmAlgorithmsSettings.activeAlgorithms;
            while(i.hasNext())
            {
                SwarmAlgorithmBase* currentAlgorithm = i.next();
                ChargeAlgorithm* chargeAlgorithm = dynamic_cast<ChargeAlgorithm*>(currentAlgorithm);
                if(chargeAlgorithm)
                {
                    if(robot->group == chargeAlgorithm->chargeGroup)
                    {
                        robot->group = nullptr;
                    }
                    else {
                        robot->group = chargeAlgorithm->chargeGroup;
                    }
                }
            }
        }
    }
}


void MainWindow::on_objectColorComboBox_currentTextChanged(const QString &color)
{
    robotDetectionSettings.objectColorTracking = color;
}

void MainWindow::loadCameraSelection()
{
    if(ui->cameraSelectionComboBox->count() != 0) return; //its already loaded so a second time is not needed
    ui->cameraSelectionComboBox->clear();

    int currentIndex = robotDetectionSettings.availableCameras.indexOf(robotDetectionSettings.selectCamera);

    for(int i = 0;i < robotDetectionSettings.availableCameras.size() ;i++)
    {
        ui->cameraSelectionComboBox->addItem( QString::number(robotDetectionSettings.availableCameras.at(i)) );
    }

    qDebug("current index %d  %d",currentIndex, robotDetectionSettings.selectCamera);
    if(currentIndex != -1)
    {
        ui->cameraSelectionComboBox->setCurrentIndex(currentIndex);
    }
}
void MainWindow::on_cameraSelectionComboBox_currentIndexChanged(int index)
{
    if(robotDetectionSettings.availableCameras.size() <= index)return;
    qDebug("camera selection %d %d   %d",index, robotDetectionSettings.availableCameras.size(), ui->cameraSelectionComboBox->count());

    robotDetectionSettings.selectCamera = robotDetectionSettings.availableCameras.at(index);
}
