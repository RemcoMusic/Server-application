#include "rectanglealgorithm.h"

RectangleAlgorithm::RectangleAlgorithm()
{
    algorithmDiscription.name = "rectangle algorithm";
    algorithmDiscription.discription = "bots drive in the shape of a rectangle";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
}

void RectangleAlgorithm::update()
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

void RectangleAlgorithm::findRobotMovementInputs()
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
        else if(distanceBetweenPoints(currentRobot->x,currentRobot->y,point1->x(),point2->y()) < 200)
        {
            point1->setX(currentRobot->x);
            point2->setY(currentRobot->y);
        }
        else if(distanceBetweenPoints(currentRobot->x,currentRobot->y,point2->x(),point1->y()) < 200)
        {
            point2->setX(currentRobot->x);
            point1->setY(currentRobot->y);
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
void RectangleAlgorithm::inputValidation()
{
    int clearance  = globalSettings.botDiameter/2;
    constrainPoint(point1, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
    constrainPoint(point2, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
}
void RectangleAlgorithm::calculatePoints()
{
    inputValidation();
    //calculate distance between markers
    int deltaX = abs(point2->rx() - point1->rx());//pytagoras A
    int deltaY = abs(point2->ry() - point1->ry());//pytagoras b


    int amountOfRobotsFittingXLines = deltaX/swarmAlgorithmsSettings.distanceBetweenRobots + 1;
    int amountOfRobotsFittingYLines = deltaY/swarmAlgorithmsSettings.distanceBetweenRobots + 1;

    //calculate the amount of robots fitting in each of the for lines and sum them
    int amountOfRobotsFitting = amountOfRobotsFittingXLines*2 + amountOfRobotsFittingYLines*2 - 4;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing <= 3)
    {
        qDebug("amountOfRobotsUsing <= 3");
        return;
    }

    double xyRatio = ((double)amountOfRobotsUsing) / amountOfRobotsFitting;
    int amountOfRobotsUsingXLines = amountOfRobotsFittingXLines * xyRatio + 1;
    int amountOfRobotsUsingYLines = (amountOfRobotsUsing - amountOfRobotsUsingXLines*2) / 2;

    int distanceBetweenRobotsXLines = (amountOfRobotsUsingYLines > 0) ? deltaX/(amountOfRobotsUsingXLines-1) : deltaX/2;
    int distanceBetweenRobotsYLines = deltaY/(amountOfRobotsUsingYLines+1   );

    if(swarmAlgorithmsSettings.debugLinearMotionSources)
    {

    }
    qDebug("%d  %d",amountOfRobotsUsing, amountOfRobotsFitting);
     qDebug("%d  %d     %d %d",amountOfRobotsUsingXLines, amountOfRobotsUsingYLines, distanceBetweenRobotsXLines, distanceBetweenRobotsYLines);
    for(int i=0;i<amountOfRobotsUsingXLines;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx()  + i * distanceBetweenRobotsXLines;
        newDestination->y = point1->ry();
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
    for(int i=0;i<amountOfRobotsUsingXLines;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx()  + i * distanceBetweenRobotsXLines;
        newDestination->y = point2->ry();
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
    for(int i=1;i<amountOfRobotsUsingYLines + 1;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx();
        newDestination->y = point1->ry() + i * distanceBetweenRobotsYLines;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
    for(int i=1;i<amountOfRobotsUsingYLines + 1;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point2->rx();
        newDestination->y = point1->ry() + i * distanceBetweenRobotsYLines;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
}

