#include "rectanglealgorithm.h"

RectangleAlgorithm::RectangleAlgorithm()
{
    algorithmDiscription.name = "rectangle algorithm";
    algorithmDiscription.discription = "bots drive in the shape of a rectangle, user inputs with balls or robot displacement are supported";
}

RectangleAlgorithm::~RectangleAlgorithm()
{
    delete point1;
    delete point2;
}

void RectangleAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
    userInputs.clear();
    if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::NONE)
    {
        point1->setX(200);
        point1->setY(200);
        point2->setX(700);
        point2->setY(700);
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

void RectangleAlgorithm::processUserInputs()
{
    //all 4 outer corners can be displaced
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
        else if(distanceBetweenPoints(currentObject->x,currentObject->y,point1->x(),point2->y()) < maximumDistanceToTrack)
        {
            point1->setX(currentObject->x);
            point2->setY(currentObject->y);
        }
        else if(distanceBetweenPoints(currentObject->x,currentObject->y,point2->x(),point1->y()) < maximumDistanceToTrack)
        {
            point2->setX(currentObject->x);
            point1->setY(currentObject->y);
        }
    }
    calculatePoints();
}
//if the input points are out of the scene the robots will also drive out of the scene, this validations keeps the points in the scene
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
    //point1 is left top, point2 is right bottom
    int deltaX = point2->rx() - point1->rx();
    int deltaY = point2->ry() - point1->ry();

    //the rectangle have 4 lines, 2 x lines and 2 y lines
    int amountOfRobotsFittingXLines = abs(deltaX)/swarmAlgorithmsSettings.distanceBetweenRobots;
    int amountOfRobotsFittingYLines = abs(deltaY)/swarmAlgorithmsSettings.distanceBetweenRobots;

    //calculate the amount of robots fitting in each of the for lines and sum them
    int amountOfRobotsFitting = amountOfRobotsFittingXLines*2 + amountOfRobotsFittingYLines*2;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing <= 3)
    {
        qDebug("amountOfRobotsUsing <= 3");
        return;
    }

    //devide robots between x and y lines
    double xyRatio = ((double)amountOfRobotsUsing) / amountOfRobotsFitting;
    int amountOfRobotsUsingXLines = amountOfRobotsFittingXLines * xyRatio;
    int amountOfRobotsUsingYLines = (amountOfRobotsUsing - amountOfRobotsUsingXLines*2) / 2;

    int distanceBetweenRobotsXLines = (amountOfRobotsUsingXLines > 0) ? deltaX/(amountOfRobotsUsingXLines) : deltaX/2;
    int distanceBetweenRobotsYLines = (amountOfRobotsUsingYLines > 0) ? deltaY/(amountOfRobotsUsingYLines) : deltaY/2;

    //draw the 4 lines
    for(int i=0;i<amountOfRobotsUsingXLines;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx()  + i * distanceBetweenRobotsXLines;
        newDestination->y = point1->ry();
        newDestination->endAngle = 0;
        destinations.append(newDestination);
    }
    for(int i=1;i<amountOfRobotsUsingXLines+1;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx()  + i * distanceBetweenRobotsXLines;
        newDestination->y = point2->ry();
        newDestination->endAngle = 0.5 * M_PI;
        destinations.append(newDestination);
    }
    for(int i=1;i<amountOfRobotsUsingYLines + 1;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point1->rx();
        newDestination->y = point1->ry() + i * distanceBetweenRobotsYLines;
        newDestination->endAngle = M_PI;
        destinations.append(newDestination);
    }
    for(int i=0;i<amountOfRobotsUsingYLines;i++)
    {
        Destination *newDestination = new Destination;
        newDestination->x = point2->rx();
        newDestination->y = point1->ry() + i * distanceBetweenRobotsYLines;
        newDestination->endAngle = 1.5 *  M_PI;
        destinations.append(newDestination);
    }
}

