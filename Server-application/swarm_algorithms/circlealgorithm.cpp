#include "circlealgorithm.h"

CircleAlgorithm::CircleAlgorithm()
{
    algorithmDiscription.name = "circle algorithm";
    algorithmDiscription.discription = "bots drive in a circle, position and size can be changed using yellow and orange objects or robots displacements";
}
void CircleAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
    userInputs.clear();
    if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::NONE)
    {
        center->setX(500);
        center->setY(500);
        outer1->setX(250);
        outer1->setY(500);
        outer2->setX(750);
        outer2->setY(500);
        calculateDestinationsCenterOuter();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::OBJECTS)
    {
        findObjectInputs(true);
        processUserInputs();
    }
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::ROBOT_MOVEMENT)
    {
        findRobotMovementInputs(data.swarmRobots);
        processUserInputs();
    }

    LinearMotionAlgorithms::update();
}


void CircleAlgorithm::processUserInputs()
{
    int ballsOuter = 0;
    bool centerUserInput = false;
    for(int i = 0;i<userInputs.size();i++)
    {
        qDebug("user input");
        Object *currentObject = userInputs.at(i);
        Ball* ball = dynamic_cast<Ball*>(currentObject);//use special color property of the ball
        if((ball == nullptr)||( ball->BallColor == Ball::BallColor::YELLOW))
        {
            if(abs(distanceFromCenter(outer1->x(),outer1->y()) - distanceFromCenter(currentObject->x,currentObject->y)) < 100)
            {
                if(ballsOuter == 0)
                {
                    outer1->rx() = currentObject->x;
                    outer1->ry() = currentObject->y;
                    ballsOuter++;
                }
                else if(ballsOuter == 1){
                    outer2->rx() = currentObject->x;
                    outer2->ry() = currentObject->y;
                    ballsOuter++;
                }
            }
        }
        if((ball != nullptr)&&(ball->BallColor == Ball::BallColor::ORANGE))
        {
            if(distanceFromCenter(currentObject->x,currentObject->y) < std::min(100, distanceFromCenter(outer1->x(),outer1->y())/2))
            {
                center->rx() = currentObject->x;
                center->ry() = currentObject->y;
                centerUserInput = true;
            }
        }
    }
    if((centerUserInput)||(ballsOuter <= 1))
    {
        calculateDestinationsCenterOuter();
    }
    else {
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

    //calculate distance between markers
    int deltaX = outer1->rx() - center->rx();//pytagoras A
    int deltaY = outer1->ry() - center->ry();//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points

    double circumference = (c *(endAngle - beginAngle));
    int amountOfRobotsFitting = circumference/swarmAlgorithmsSettings.distanceBetweenRobots;

    int amountOfRobotsUsing = std::min(amountOfRobotsFitting, data.swarmRobots.size());
    if(amountOfRobotsUsing < 1)
    {
        //qDebug("amount of robots using < 1");
        return;
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
