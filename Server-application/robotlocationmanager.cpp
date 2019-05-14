#include "robotlocationmanager.h"
RobotLocationManager robotLocationManager;
RobotLocationManager::RobotLocationManager()
{

}

void RobotLocationManager::printAllRobots()
{
    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        i.next()->print();
    }
}
