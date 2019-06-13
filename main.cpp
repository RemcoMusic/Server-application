#include "mainwindow.h"
#include <QApplication>
#include "swarmalgorithms.h"
#include "robotconnection.h"
#include "robotdetection.h"
#include "swarmsimulation.h"
#include "locationmanager.h"
#include <QDebug>
#include <QObject>


int main(int argc, char *argv[])
{

    //visualisation
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //swarm algorithms
    SwarmAlgorithms swarmAlgorithms;
    qDebug() << "swarmAlgorithms Started!" << endl;
    //wifi connection to the physical swarm robots
    RobotConnection robotConnection;
    qDebug() << "robotConnection Started!" << endl;
    SwarmSimulation swarmSimulation;
    qDebug() << "swarmSimulation Started!" << endl;
    robotDetection robotDetection;
    robotDetection.start();
    qDebug() << "robotDetection Started!" << endl;
    qDebug() << "setting up signals and slots" << endl;

    bool s = QObject::connect(&robotDetection,SIGNAL(makeANewRobot(int,int)),&locationManager,SLOT(makeNewRealRobot(int,int)));
    //robotLocationManager.makeNewRealRobot(500,500);
    qDebug() << s;
    QObject::connect(&robotDetection,SIGNAL(newFrameFinished()),&swarmSimulation,SLOT(startSimulation()));
    QObject::connect(&swarmSimulation,SIGNAL(simulationFinished()),&swarmAlgorithms,SLOT(update()));
    QObject::connect(&swarmAlgorithms,SIGNAL(algoritmFinished()),&robotConnection,SLOT(connectionloop()));
    QObject::connect(&robotConnection,SIGNAL(done()),&w,SLOT(updateGui()));


    return a.exec();
}