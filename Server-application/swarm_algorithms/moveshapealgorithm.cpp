#include "swarm_algorithms/moveshapealgorithm.h"

#include <robotlocation.h>

MoveShapeAlgorithm::MoveShapeAlgorithm()
{
    algorithmDiscription.name = "moving shape";
    algorithmDiscription.discription = "this is a test algorithm";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 10;
}
void MoveShapeAlgorithm::update()
{
    int preferedX = 500;
    int preferedY = 500;
    qDebug("update move shape algorithm");
    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        RobotLocation* robot = i.next();
        if(robot->x > preferedX)
        {
            robot->x -=2;
        }
        else if(robot->x < preferedX){
            robot->x +=2;
        }
    }
}
