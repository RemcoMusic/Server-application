#include "trianglealgorithm.h"

TriangleAlgorithm::TriangleAlgorithm()
{

}

TriangleAlgorithm::~TriangleAlgorithm()
{
    delete point1;
    delete point2;
    delete point3;
}

void TriangleAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
    userInputs.clear();
    if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::NONE)
    {
        point1->setX(globalSettings.fieldSizeX/2);
        point1->setY(globalSettings.fieldSizeY/2-300);
        point2->setX(globalSettings.fieldSizeX/2 + 250);
        point2->setY(globalSettings.fieldSizeY/2 + 250);
        point3->setX(globalSettings.fieldSizeX/2 - 250);
        point3->setY(globalSettings.fieldSizeY/2 + 250);
        calculatePoints();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::OBJECTS)
    {
        findObjectInputs();
        processUserInputs();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::ROBOT_MOVEMENT)
    {
        findRobotMovementInputs(data.swarmRobots);
        processUserInputs();
    }
    LinearMotionAlgorithms::update();
}

void TriangleAlgorithm::inputValidation()
{
    int clearance  = globalSettings.botDiameter/2;
    constrainPoint(point1, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
    constrainPoint(point2, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
    constrainPoint(point3, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY-clearance);
}
int assignNumBots(int length , int remainingLineLenght,int numBotsToSpare){ // helper function, not in the header
    return std::round((double)length/(double)remainingLineLenght*numBotsToSpare);
}
void TriangleAlgorithm::calculatePoints()
{
    int line1Length = distanceBetweenPoints(point1->x(),point1->y(),point2->x(),point2->y());
    int line2Length = distanceBetweenPoints(point2->x(),point2->y(),point3->x(),point3->y());
    int line3Length = distanceBetweenPoints(point3->x(),point3->y(),point1->x(),point1->y());

    int amountOfRobotsFittingLine1 = line1Length/swarmAlgorithmsSettings.distanceBetweenRobots;
    int amountOfRobotsFittingLine2 = line2Length/swarmAlgorithmsSettings.distanceBetweenRobots;
    int amountOfRobotsFittingLine3 = line3Length/swarmAlgorithmsSettings.distanceBetweenRobots;

    int amountOfRobotsFitting = amountOfRobotsFittingLine1 + amountOfRobotsFittingLine2 + amountOfRobotsFittingLine3;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());

    if(amountOfRobotsUsing <= 2)
    {
        qDebug("amountOfRobotsUsing <= 2");
        return;
    }
    //double ratio = ((double)amountOfRobotsUsing) / amountOfRobotsFitting;
    int amountOfRobotsUsingLine1 = assignNumBots(line1Length,line1Length+line2Length+line3Length,amountOfRobotsUsing);
    int amountOfRobotsUsingLine2 = assignNumBots(line2Length,line2Length+line3Length,amountOfRobotsUsing-amountOfRobotsUsingLine1);
    int amountOfRobotsUsingLine3 = assignNumBots(line3Length,line3Length,amountOfRobotsUsing-amountOfRobotsUsingLine1-amountOfRobotsUsingLine2);

    int distanceBetweenRobotsLine1 = line1Length/amountOfRobotsUsingLine1;
    int distanceBetweenRobotsLine2 = line2Length/amountOfRobotsUsingLine2;
    int distanceBetweenRobotsLine3 = line3Length/amountOfRobotsUsingLine3;
    //draw the 3 lines
    double angleLine1 = atan2(point2->y()-point1->y(),point2->x()-point1->x());
    //qDebug("%f, %f, %d",ratio,angleLine1,amountOfRobotsUsingLine1);

    for(int i = 0; i< amountOfRobotsUsingLine1;i++){
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx()  + cos(angleLine1) * i * distanceBetweenRobotsLine1;
        newDestination->y = point1->ry()  + sin(angleLine1) * i * distanceBetweenRobotsLine1;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }

    double angleLine2 = atan2(point3->y()-point2->y(),point3->x()-point2->x());
    for(int i = 0; i< amountOfRobotsUsingLine2;i++){
        Destination *newDestination = new Destination;
        newDestination->x = point2->rx()  + cos(angleLine2) * i * distanceBetweenRobotsLine2;
        newDestination->y = point2->ry()  + sin(angleLine2) * i * distanceBetweenRobotsLine2;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }

    double angleLine3 = atan2(point1->y()-point3->y(),point1->x()-point3->x());
    for(int i = 0; i< amountOfRobotsUsingLine3;i++){
        Destination *newDestination = new Destination;
        newDestination->x = point3->rx()  + cos(angleLine3) * i * distanceBetweenRobotsLine3;
        newDestination->y = point3->ry()  + sin(angleLine3) * i * distanceBetweenRobotsLine3;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
}

void TriangleAlgorithm::calculateDestination()
{

}

void TriangleAlgorithm::processUserInputs()
{

    int maximumDistanceToTrack = swarmAlgorithmsSettings.distanceBetweenRobots;
    QListIterator<Object*> iterator(userInputs);
    while (iterator.hasNext())
    {
        Object *currentObject = iterator.next();
        if(distanceBetweenPoints(currentObject->x,currentObject->y,point1->x(),point1->y()) < maximumDistanceToTrack)
        {
            point1->setX(currentObject->x);
            point1->setY(currentObject->y);
        }
        else if(distanceBetweenPoints(currentObject->x,currentObject->y,point2->x(),point2->y()) < maximumDistanceToTrack)
        {
            point2->setX(currentObject->x);
            point2->setY(currentObject->y);
        }
        else if(distanceBetweenPoints(currentObject->x,currentObject->y,point3->x(),point3->y()) < maximumDistanceToTrack)
        {
            point3->setX(currentObject->x);
            point3->setY(currentObject->y);
        }

    }
    calculatePoints();
}
