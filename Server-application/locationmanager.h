//Swarmbotron application
//Rene Schouten
//5-2019
//class that mangage all robotLocation objects which represent real or simulated robots of the swarm
#pragma once

#include <QObject>
#include "robotlocation.h"
#include "robotgroup.h"
#include <QList>
#include "objectsbase.h"
#include "simulatedrobot.h"
#include "mainwindow.h"

class LocationManager: public QObject
{
    Q_OBJECT
public:
    LocationManager();
    QList<RobotLocation*> robots;//list of all robots in the field
    QList<RobotGroup*> groups;//list of different groups of robots

    QList<Object*>objects;//list of objects in the field

    static QList<Object*> currentSelectedObjects;

    void printAllRobots();
    RobotLocation* addSimulatedRobot(RobotGroup* group = nullptr);
    void deleteAllSimulatedRobots();
    void deleteAllSimulatedRobotsFromGroup(RobotGroup* group = nullptr);
    void addObject(Object* object);
    void turnOffAllRobots();
    void resetEverything();
public slots:
    void makeNewRealRobot(int x,int y);
};
extern LocationManager locationManager;
