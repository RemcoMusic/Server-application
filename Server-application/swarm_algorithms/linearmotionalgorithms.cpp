#include "linearmotionalgorithms.h"

LinearMotionAlgorithms::LinearMotionAlgorithms()
{

}
void LinearMotionAlgorithms::update()
{
    calculateDestination();
}

inline int distanceBetweenPoints(LinearMotionAlgorithms::Destination* destination1, QPoint* destination2)
{
    int deltaX = abs(destination1->x - destination2->x());//pytagoras A
    int deltaY = abs(destination1->y - destination2->y());//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
    return c;
}
bool sortMethod(const LinearMotionAlgorithms::DistanceObject* distanceObject1,const LinearMotionAlgorithms::DistanceObject* distanceObject2)
{
    return distanceObject1->distance > distanceObject2->distance;
}
void LinearMotionAlgorithms::moveRobotTo(RobotLocation *robot,Destination *destination)
{
    int deltaX = destination->x - robot->location->x();
    int deltaY = destination->y - robot->location->y();
    double angle = atan2(deltaY,deltaX);
    int newX = robot->location->x() + cos(angle) * 0.5;
    int newY = robot->location->y() + sin(angle) * 0.5;
    robot->location->setX(newX);
    robot->location->setY(newY);


}
void LinearMotionAlgorithms::calculateDestination()
{
    qDebug("run linearMotionAlgoritm");

    QListIterator<Destination*> destinationList(destinations);
    while (destinationList.hasNext())
        destinationList.next()->occupied=false;


    QList<DistanceObject*> distanceObjects;

    QListIterator<RobotLocation*> robotList(robotLocationManager.robots);
    while (robotList.hasNext())
    {
        RobotLocation *robot = robotList.next();
        if(robot->group == robotGroup)
        {
            DistanceObject *nearestDestination = new DistanceObject;
            nearestDestination->distance = INT_MAX;
            QListIterator<Destination*> destinationList(destinations);
            while (destinationList.hasNext())
            {
                Destination *destination = destinationList.next();
                int distance = distanceBetweenPoints(destination,robot->location);
                if(distance < nearestDestination->distance)
                {
                    nearestDestination->distance = distance;
                    nearestDestination->robot = robot;
                }
            }
            distanceObjects.append(nearestDestination);
        }
    }

    qSort(distanceObjects.begin(),distanceObjects.end(),sortMethod);

    int ignoreRobots = std::max(0,robotLocationManager.robots.size() - distanceObjects.size());//ignore all robots until, because there are not enough points
    int index = 0;

    QListIterator<DistanceObject*> distanceObjectsList(distanceObjects);
    while (distanceObjectsList.hasNext())
    {
        DistanceObject *distanceObject = distanceObjectsList.next();
        if(distanceObject->robot->group == robotGroup)
        {
            if(index<ignoreRobots)
            {
                qDebug("ignore");
            }
            else {

            }
                qDebug("%d",distanceObject->distance);

                Destination *nearestDestination = nullptr;
                int shortestDistance = INT_MAX;
                QListIterator<Destination*> destinationList(destinations);
                while (destinationList.hasNext())
                {
                    Destination *destination = destinationList.next();
                    if(destination->occupied == false)
                    {
                        int distance = distanceBetweenPoints(destination,distanceObject->robot->location);
                        qDebug("    %d",distance);
                        if(distance < shortestDistance)
                        {
                            nearestDestination = destination;
                            shortestDistance = distance;
                        }
                    }
                }
                if(nearestDestination != nullptr)
                {
                    //moveRobotTo(distanceObject->robot, nearestDestination);
                    nearestDestination->robot = distanceObject->robot;
                    nearestDestination->occupied = true;
                    qDebug("   -> %d",shortestDistance);
                }
        }

        index++;
    }
}


