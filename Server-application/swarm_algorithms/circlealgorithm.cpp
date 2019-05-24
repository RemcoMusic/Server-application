#include "circlealgorithm.h"

CircleAlgorithm::CircleAlgorithm()
{
    algorithmDiscription.name = "circle algorithm";
    algorithmDiscription.discription = "bots drive in a circle defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
}
void CircleAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    destinations.clear();
    if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::NONE)
    {
        calculateDestinationsCenterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::HAND_GESTURE)
    {
        calculateDestinationsCenterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::REAL_OBJECTS_CENTER_OUTER)
    {
        calculateDestinationsCenterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::REAL_OBJECTS_OUTER_OUTER)
    {
        calculateDestinationsOuterOuter();
    }

    LinearMotionAlgorithms::update();
}
void CircleAlgorithm::calculateDestinationsOuterAngle()
{

}
void CircleAlgorithm::calculateDestinationsOuterOuter()
{
    //this method uses two outer places of the circle, it calculates the center so the center-outer method can do the rest
    int deltaX = outer2->x() - outer1->x();
    int deltaY = outer2->y() - outer1->y();
    center->rx() = outer1->x() + deltaX / 2;
    center->ry() = outer1->y() + deltaY / 2;
    calculateDestinationsCenterOuter();
}
void CircleAlgorithm::calculateDestinationsCenterOuter()
{
    //calculate distance between markers
    int deltaX = center->rx() - outer1->rx();//pytagoras A
    int deltaY = center->ry() - outer1->ry();//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points

    double circumference = (2 * c * M_PI);
    int amountOfRobotsFitting = circumference/swarmAlgorithmsSettings.distanceBetweenRobots;

    qDebug("%d",data.swarmRobots.size());
    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());

    int distanceBetweenBots = circumference/amountOfRobotsUsing;
    double angleBetweenRobots = 2 * M_PI/amountOfRobotsUsing;
    if(swarmAlgorithmsSettings.debugLinearMotionSources)
    {
        qDebug("distance between points %d",c);
        qDebug("amount of bots fitting %d",amountOfRobotsFitting);
        qDebug("distance between bots %d",distanceBetweenBots);
        qDebug("angle between bots %f",angleBetweenRobots);
    }
    double angle = 0;
    for(int i=0;i<amountOfRobotsUsing;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = center->x() + cos(angle) * c;
        newDestination->y = center->y() + sin(angle) * c;
        destinations.append(newDestination);
        //qDebug("new position %d, %d",newDestination->x,newDestination->y);

        angle+=angleBetweenRobots;
    }
}
