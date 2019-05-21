//Swarmbotron application
//Rene Schouten
//5-2019
//class that mangage all robotLocation objects which represent real or simulated robots of the swarm
#ifndef ROBOTLOCATIONMANAGER_H
#define ROBOTLOCATIONMANAGER_H

#include <QObject>
#include "robotlocation.h"
#include "robotgroup.h"
#include <QList>
class RobotLocationManager: public QObject
{
    Q_OBJECT
public:
    RobotLocationManager();
    QList<RobotLocation*> robots;
    QList<RobotGroup*> groups;

    void printAllRobots();
    RobotLocation* addSimulatedRobot(RobotGroup* group = nullptr);
    void deleteAllSimulatedRobots();
    void deleteAllSimulatedRobotsFromGroup(RobotGroup* group = nullptr);

public slots:
    void makeNewRealRobot(int x,int y);
};
extern RobotLocationManager robotLocationManager;
#endif // ROBOTLOCATIONMANAGER_H
