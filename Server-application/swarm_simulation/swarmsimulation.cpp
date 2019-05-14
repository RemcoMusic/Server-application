#include "swarmsimulation.h"

#include <swarmalgorithmbase.h>

SwarmSimulation::SwarmSimulation()
{

}

RobotLocation *SwarmSimulation::addSimulatedRobot(RobotGroup *group)
{
    RobotLocation *newRobot = new RobotLocation(group);
    newRobot->type = RobotLocation::RobotType::SIMULATED;
    robotLocationManager.robots.append(newRobot);
}
void SwarmSimulation::deleteAllSimulatedRobots()
{
    QMutableListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        if(i.next()->type == RobotLocation::RobotType::SIMULATED)
        {
            i.remove();
        }
    }
}
void SwarmSimulation::deleteAllSimulatedRobotsFromGroup(RobotGroup *group)
{
    QMutableListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        auto val = i.next();
        if(val->type == RobotLocation::RobotType::SIMULATED)
        {
            if(val->group == group)
            {
                i.remove();
            }
        }
    }
}
