#include "mainwindow.h"
#include <QApplication>
#include "swarmalgorithms.h"
#include "robotconnection.h"
#include "robotdetection.h"
#include "swarmsimulation.h"
int main(int argc, char *argv[])
{
    //visualisation
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //swarm algorithms
    SwarmAlgorithms swarmAlgorithms;

    //wifi connection to the physical swarm robots
    RobotConnection robotConnection;


    robotDetection robotDetection;

    SwarmSimulation swarmSimulation;

    return a.exec();
}
