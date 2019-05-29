#include "linealgorithm.h"
#include "linearmotionalgorithms.h"

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
static int distanceBetweenPoints(int x1, int y1, int x2, int y2)
{
    int deltaX = x1 - x2;//pytagoras A
    int deltaY = y1 - y2;//pytagoras b
    return sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
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
            qDebug("1");
        }
        else if(distanceBetweenPoints(currentRobot->x,currentRobot->y,point2->x(),point2->y()) < 200)
        {
            point2->setX(currentRobot->x);
            point2->setY(currentRobot->y);
            qDebug("2");
        }
    }
    calculatePoints();
}
void LineAlgorithm::calculatePoints()
{
    //calculate distance between markers
    int deltaX = point2->rx() - point1->rx();//pytagoras A
    int deltaY = point2->ry() - point1->ry();//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points

    int amountOfRobotsFitting = c/swarmAlgorithmsSettings.distanceBetweenRobots;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing <= 1)
    {
        qDebug("amountOfRobotsUsing <= 1");
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

