#include "swarmsimulation.h"
#include "swarmsimulationsettings.h"

#include <swarmalgorithmbase.h>

SwarmSimulation::SwarmSimulation()
{

}
void SwarmSimulation::moveRobot(RobotLocation *robot)
{
    double deltaX = robot->destinationX - robot->x;
    double deltaY = robot->destinationY - robot->y;

    if((abs(deltaX) <= 1) && (abs(deltaY) <= 1))return;//already on location

    double goalAngle = atan2(deltaY,deltaX);
    double currentAngle = robot->angle * (M_PI / 180);
    if(abs(goalAngle - currentAngle) > M_PI)
    {
        currentAngle += M_PI;
    }
    if(currentAngle > 2*M_PI)
    {
        currentAngle -= 2*M_PI;
    }
    robot->x = robot->x + std::fmin(cos(goalAngle) * robot->speed * swarmSimulationSettings.maxSpeed, abs(deltaX));
    robot->y = robot->y + std::fmin(sin(goalAngle) * robot->speed * swarmSimulationSettings.maxSpeed, abs(deltaY));
}
void SwarmSimulation::startSimulation()
{
    qDebug() << "start simulation called" << endl;

    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->type == RobotLocation::RobotType::SIMULATED)
        {
             moveRobot(currentRobot);
        }
    }



    emit simulationFinished();
}

