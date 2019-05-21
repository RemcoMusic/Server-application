#include "circlealgorithm.h"

CircleAlgorithm::CircleAlgorithm()
{
    algorithmDiscription.name = "circle algorithm";
    algorithmDiscription.discription = "bots drive in a circle defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
    calculatePoints();
}
void CircleAlgorithm::update()
{
    calculatePoints();
    LinearMotionAlgorithms::update();
}
void CircleAlgorithm::calculatePoints()
{
    destinations.clear();
    //calculate distance between markers
    int deltaX = abs(point1->rx() - point2->rx());//pytagoras A
    int deltaY = abs(point1->ry() - point2->ry());//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
    qDebug("distance between points %d",c);
    double circumference = (2 * c * M_PI);
    int amountOfRobotsFitting = circumference/swarmAlgorithmsSettings.distanceBetweenRobots;
    qDebug("amount of bots fitting %d",amountOfRobotsFitting);
    int distanceBetweenBots = circumference/amountOfRobotsFitting;
    qDebug("distance between bots %d",distanceBetweenBots);
    double angleBetweenRobots = 2 * M_PI/amountOfRobotsFitting;
    qDebug("angle between bots %f",angleBetweenRobots);

    double angle = 0;
    for(int i=0;i<amountOfRobotsFitting;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->x() + cos(angle) * c;
        newDestination->y = point1->y() + sin(angle) * c;
        destinations.append(newDestination);
        //qDebug("new position %d, %d",newDestination->x,newDestination->y);

        angle+=angleBetweenRobots;
    }
}
