#ifndef SWARMSIMULATION_H
#define SWARMSIMULATION_H

#include <QObject>
#include <QDebug>
#include "robotlocation.h"
#include "locationmanager.h"
#include <math.h>
#include <QGenericMatrix>
#include <swarmalgorithmbase.h>
#include <time.h>
#include "globalhelperfunctions.h"

//arduino codes
#include <Arduino.h>
#include "motorDriver.h"

extern LocationManager locationManager;
class SwarmSimulation: public QObject
{
    Q_OBJECT
    void moveRobot(RobotLocation *robot);
    void moveRobotRealistic(RobotLocation *robot);
    void moveWheels(double Vl, double Vr, RobotLocation *robot);
    clock_t lastTime;
    double deltaT=0;

    void robotCodeSimulation(RobotLocation *robot);
public:
    SwarmSimulation();
public slots:
    void startSimulation();
signals:
    void simulationFinished();
};

#endif // SWARMSIMULATION_H
