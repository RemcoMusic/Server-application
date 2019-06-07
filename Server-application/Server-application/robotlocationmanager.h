//Swarmbotron application
//Rene Schouten
//5-2019
//class that mangage all robotLocation objects which represent real or simulated robots of the swarm
#ifndef ROBOTLOCATIONMANAGER_H
#define ROBOTLOCATIONMANAGER_H

#include <QObject>
#include "robotlocation.h"
#include <QList>
class RobotLocationManager
{
public:
    RobotLocationManager();
    QList<RobotLocation> robots;
};

#endif // ROBOTLOCATIONMANAGER_H
