#include "linealgorithm.h"
#include "linearmotionalgorithms.h"

LineAlgorithm::LineAlgorithm()
{
    algorithmDiscription.name = "line algorithm";
    algorithmDiscription.discription = "bots ride in a line defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
    calculatePoints();
}

void LineAlgorithm::update()
{
    LinearMotionAlgorithms::update();
}
void LineAlgorithm::calculatePoints()
{
    destinations.clear();
    //calculate distance between markers
    int deltaX = abs(point1->rx() - point2->rx());//pytagoras A
    int deltaY = abs(point1->ry() - point2->ry());//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
    qDebug("distance between points %d",c);
    int amountOfRobotsFitting = c/swarmAlgorithmsSettings.distanceBetweenRobots;
     qDebug("amount of bots fitting %d",amountOfRobotsFitting);
    int distanceBetweenBots = c/amountOfRobotsFitting;
     qDebug("distance between bots %d",distanceBetweenBots);

    double angle = atan2(deltaY,deltaX);
    qDebug("line angle %f",angle);
    for(int i=0;i<amountOfRobotsFitting;i++)
    {
        Destination *newDestination = new Destination;

        newDestination->x = std::min(point1->rx(),point2->rx()) + cos(angle) * distanceBetweenBots*i;
        newDestination->y = std::min(point1->ry(),point2->ry()) + sin(angle) * distanceBetweenBots*i;
        destinations.append(newDestination);
        qDebug("new position %d, %d",newDestination->x,newDestination->y);
    }

}

