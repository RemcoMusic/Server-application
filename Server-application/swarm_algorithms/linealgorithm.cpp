#include "linealgorithm.h"

LineAlgorithm::LineAlgorithm()
{
    algorithmDiscription.name = "line algorithm";
    algorithmDiscription.discription = "bots ride in a line defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
}

void LineAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
    if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::NONE)
    {
        calculatePoints();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::HAND_GESTURE)
    {
        calculatePoints();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::REAL_OBJECTS_CENTER_OUTER)
    {
        calculatePoints();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::REAL_OBJECTS_OUTER_OUTER)
    {
        calculatePoints();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::ROBOT_MOVEMENT)
    {
        findRobotMovementInputs();
    }
    LinearMotionAlgorithms::update();
}

void LineAlgorithm::findRobotMovementInputs()
{
    QList<RobotLocation*> userInputs;
    QListIterator<RobotLocation*> i(data.swarmRobots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->userInput)
        {
            userInputs.append(currentRobot);
        }
    }
    QListIterator<RobotLocation*> iterator(userInputs);
    while (iterator.hasNext())
    {
        RobotLocation *currentRobot = iterator.next();
        if(distanceBetweenPoints(currentRobot->x,currentRobot->y,point1->x(),point1->y()) < 200)
        {
            point1->setX(currentRobot->x);
            point1->setY(currentRobot->y);
        }
        else if(distanceBetweenPoints(currentRobot->x,currentRobot->y,point2->x(),point2->y()) < 200)
        {
            point2->setX(currentRobot->x);
            point2->setY(currentRobot->y);
        }
    }
    calculatePoints();
}
static void constrainPoint(QPoint *point, int xMin, int yMin, int xMax, int yMax)
{
    point->rx() = std::max(xMin, point->x());
    point->ry() = std::max(yMin, point->y());
    point->rx() = std::min(xMax, point->x());
    point->ry() = std::min(yMax, point->y());
}
void LineAlgorithm::inputValidation()
{
    int clearance  = globalSettings.botDiameter/2;
    constrainPoint(point1, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
    constrainPoint(point2, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
}
void LineAlgorithm::calculatePoints()
{
    inputValidation();
    //calculate distance between markers
    int deltaX = point2->rx() - point1->rx();//pytagoras A
    int deltaY = point2->ry() - point1->ry();//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points

    int amountOfRobotsFitting = c/swarmAlgorithmsSettings.distanceBetweenRobots;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing <= 1)
    {
        //qDebug("amountOfRobotsUsing <= 1");
        return;
    }
    int distanceBetweenBots = c/(amountOfRobotsUsing-1);

    double angle = atan2(deltaY,deltaX);
    if(swarmAlgorithmsSettings.debugLinearMotionSources)
    {
        qDebug("distance between points %d",c);
        qDebug("amount of bots fitting %d",amountOfRobotsFitting);
        qDebug("distance between bots %d",distanceBetweenBots);
        qDebug("line angle %f",angle);
    }
    for(int i=0;i<amountOfRobotsUsing;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx() + cos(angle) * distanceBetweenBots * i;
        newDestination->y = point1->ry() + sin(angle) * distanceBetweenBots * i;
        newDestination->endAngle = angle;
        destinations.append(newDestination);
        if(swarmAlgorithmsSettings.debugLinearMotionSources)
        {
            qDebug("new position %d, %d",newDestination->x,newDestination->y);
        }
    }

}

