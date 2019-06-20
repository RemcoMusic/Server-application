#include "robotdisplacementdetection.h"


RobotDisplacementDetection::RobotDisplacementDetection()
{

}
void RobotDisplacementDetection::applyComplementeryFilter(RobotLocation* robot)
{
    double factor1 = swarmAlgorithmsSettings.dispacementComplementeryFilter;
    double factor2 = 1.0 - swarmAlgorithmsSettings.dispacementComplementeryFilter;
    robot->simulatedRobot->x = round(robot->x * factor2 + robot->simulatedRobot->x * factor1);
    robot->simulatedRobot->y = round(robot->y * factor2 + robot->simulatedRobot->y * factor1);
    robot->simulatedRobot->angle = robot->angle * factor2 + robot->simulatedRobot->angle * factor1;
}
void RobotDisplacementDetection::update()
{
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        int distance = distanceBetweenPoints(currentRobot, currentRobot->simulatedRobot);
        double deltaAngle = calculateDeltaAngle(currentRobot->angle, currentRobot->simulatedRobot->angle);
        distance += abs(deltaAngle) * 30;
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
