#include "circlealgorithm.h"

#include <simulatedrobot.h>

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
    LinearMotionAlgorithms::clearDestinations();
    userInputs.clear();
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
        findObjectInputs(true);
        processUserInputsCenterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::REAL_OBJECTS_OUTER_OUTER)
    {
        findObjectInputs(true);
        processUserInputsOuterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::ROBOT_MOVEMENT)
    {
        findRobotMovementInputs();
        processUserInputsOuterOuter();
    }

    LinearMotionAlgorithms::update();
}
void CircleAlgorithm::findObjectInputs(bool simulated)
{
    QListIterator<Object*> i(locationManager.objects);
    while (i.hasNext())
    {
        Object *currentObject = i.next();
        if(dynamic_cast<Ball*>(currentObject) != nullptr)
        {
            userInputs.append(currentObject);
        }
    }
}
void CircleAlgorithm::findRobotMovementInputs()
{
    QListIterator<RobotLocation*> i(data.swarmRobots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->userInput)
        {
            userInputs.append(currentRobot);
        }
    }
}

void CircleAlgorithm::processUserInputsCenterOuter()
{
    for(int i = 0;i<userInputs.size();i++)
    {
        Object *currentObject = userInputs.at(i);
        if(abs(distanceFromCenter(outer1->x(),outer1->y()) - distanceFromCenter(currentObject->x,currentObject->y)) < 100)
        {
            outer1->rx() = currentObject->x;
            outer1->ry() = currentObject->y;
        }
        else if(distanceFromCenter(currentObject->x,currentObject->y) < 100)
        {
            center->rx() = currentObject->x;
            center->ry() = currentObject->y;
        }
    }
    calculateDestinationsCenterOuter();
}
void CircleAlgorithm::processUserInputsOuterOuter()
{
    if(userInputs.size() == 0)
    {
        calculateDestinationsCenterOuter();
    }
    else if(userInputs.size() == 1)
    {

        Object *currentObject = userInputs.first();
        //first check if the robot is near the radius of the circle
        if(abs(distanceFromCenter(outer1->x(),outer1->y()) - distanceFromCenter(currentObject->x,currentObject->y)) < 100)
        {
            outer1->rx() = currentObject->x;
            outer1->ry() = currentObject->y;
        }
        calculateDestinationsCenterOuter();
    }
    else
    {
        Object *object1 = userInputs.first();
        Object *object2 = userInputs.at(1);
        outer1->rx() = object1->x;
        outer1->ry() = object1->y;
        outer2->rx() = object2->x;
        outer2->ry() = object2->y;
        calculateDestinationsOuterOuter();
    }
}
int CircleAlgorithm::distanceFromCenter(int x, int y)
{
    int deltaX = center->rx() - x;//pytagoras A
    int deltaY = center->ry() - y;//pytagoras b
    return  sqrt(deltaX*deltaX + deltaY*deltaY);
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
    int deltaX = outer1->rx() - center->rx();//pytagoras A
    int deltaY = outer1->ry() - center->ry();//pytagoras b
    double beginAngle = atan2(deltaY, deltaX);
    calculateDestinationsCenterOuter(beginAngle,beginAngle + 2*M_PI);
}
static void constrainPoint(QPoint *point, int xMin, int yMin, int xMax, int yMax)
{
    point->rx() = std::max(xMin, point->x());
    point->ry() = std::max(yMin, point->y());
    point->rx() = std::min(xMax, point->x());
    point->ry() = std::min(yMax, point->y());
}
void CircleAlgorithm::inputValidation()
{
    int clearance  = globalSettings.botDiameter/2;
    constrainPoint(outer1, clearance, clearance, globalSettings.fieldSizeX, globalSettings.fieldSizeY);
    int clearanceCenter = clearance + distanceFromCenter(outer1->x(), outer1->y());
    constrainPoint(center, clearanceCenter, clearanceCenter, globalSettings.fieldSizeX-clearanceCenter, globalSettings.fieldSizeY-clearanceCenter);
}
void CircleAlgorithm::calculateDestinationsCenterOuter(double beginAngle, double endAngle, bool addExtra)
{
    inputValidation();
    if(endAngle <= beginAngle)qFatal("calculateDestinationsCenterOuter endAngle <= beginAngle");
    qDebug("%f , %f",beginAngle,endAngle);

    //calculate distance between markers
    int deltaX = outer1->rx() - center->rx();//pytagoras A
    int deltaY = outer1->ry() - center->ry();//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points

    double circumference = (c *(endAngle - beginAngle));
    int amountOfRobotsFitting = circumference/swarmAlgorithmsSettings.distanceBetweenRobots;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing < 1)
    {
        qFatal("fatal amount of robots using < 1");
    }

    double angleBetweenRobots = (endAngle - beginAngle)/(amountOfRobotsUsing);
    if(addExtra)
    {
        angleBetweenRobots = (endAngle - beginAngle)/(amountOfRobotsUsing-1);
    }
    if(swarmAlgorithmsSettings.debugLinearMotionSources)
    {
        qDebug("distance between points %d",c);
        qDebug("amount of bots fitting %d",amountOfRobotsFitting);
        qDebug("angle between bots %f",angleBetweenRobots);
    }
    double angle = beginAngle;
    for(int i=0;i<amountOfRobotsUsing;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = center->x() + cos(angle) * c;
        newDestination->y = center->y() + sin(angle) * c;
        newDestination->endAngle = angle;
        destinations.append(newDestination);
        //qDebug("new position %d, %d",newDestination->x,newDestination->y);

        angle+=angleBetweenRobots;
    }
}
