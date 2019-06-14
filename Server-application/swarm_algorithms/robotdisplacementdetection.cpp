#include "robotdisplacementdetection.h"


RobotDisplacementDetection::RobotDisplacementDetection()
{

}
void RobotDisplacementDetection::applyComplementeryFilter(RobotLocation* robot)
{
    robot->simulatedRobot->x = round(robot->x * 0.05 + robot->simulatedRobot->x * 0.95);
    robot->simulatedRobot->y = round(robot->y * 0.05 + robot->simulatedRobot->y * 0.95);
    robot->simulatedRobot->angle = robot->angle * 0.05 + robot->simulatedRobot->angle * 0.95;
}
void RobotDisplacementDetection::update()
{
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        int distance = distanceBetweenPoints(currentRobot, currentRobot->simulatedRobot);
        if(distance > 50)
        {
            currentRobot->lastDisplacement = clock();
            currentRobot->userInput = true;
        }
        else {
            if((clock()-currentRobot->lastDisplacement) > swarmAlgorithmsSettings.displacementKeepTimeMS)
            {
                currentRobot->userInput = false;
            }
        }
        applyComplementeryFilter(currentRobot);
    }
}
void RobotDisplacementDetection::sync()
{
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        currentRobot->simulatedRobot->destinationX = currentRobot->destinationX;
        currentRobot->simulatedRobot->destinationY = currentRobot->destinationY;
        currentRobot->simulatedRobot->speed = currentRobot->speed;
        currentRobot->simulatedRobot->endAngle = currentRobot->endAngle;

    }
}
