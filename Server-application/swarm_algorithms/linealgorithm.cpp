#include "linealgorithm.h"

LineAlgorithm::LineAlgorithm()
{
    algorithmDiscription.name = "line algorithm";
    algorithmDiscription.discription = "bots ride in a line defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
    points.append(new QPoint(500,500));
    points.append(new QPoint(400,400));
    calculatePoints();
}

void LineAlgorithm::update()
{

}
void LineAlgorithm::calculatePoints()
{
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
        QPoint *newPoint = new QPoint();
        newPoint->rx() = std::min(point1->rx(),point2->rx()) + cos(angle) * distanceBetweenBots*i;
        newPoint->ry() = std::min(point1->ry(),point2->ry()) + sin(angle) * distanceBetweenBots*i;

        qDebug("new position %d, %d",newPoint->rx(),newPoint->ry());
    }

}

