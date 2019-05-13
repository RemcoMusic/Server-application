#ifndef SWARMSIMULATION_H
#define SWARMSIMULATION_H

#include <QObject>
#include "robotlocation.h"
#include "robotlocationmanager.h"
extern RobotLocationManager robotLocationManager;
class SwarmSimulation
{
public:
    SwarmSimulation();
    RobotLocation* addSimulatedRobot(RobotGroup* group = nullptr);
    void deleteAllSimulatedRobots();
    void deleteAllSimulatedRobotsFromGroup(RobotGroup* group = nullptr);
};

#endif // SWARMSIMULATION_H
