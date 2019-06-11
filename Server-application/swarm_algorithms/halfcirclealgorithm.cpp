#include "halfcirclealgorithm.h"

HalfCircleAlgorithm::HalfCircleAlgorithm()
{
    algorithmDiscription.name = "circle algorithm";
    algorithmDiscription.discription = "bots drive in a circle defined by red objects";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
}
void HalfCircleAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
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
    else if(swarmAlgorithmsSettings.inputSource == SwarmAlgorithmsSettings::AlgorithmInputSource::ROBOT_MOVEMENT)
    {
        findRobotMovementInputs();
    }

    LinearMotionAlgorithms::update();
}
static bool compereUserInputs(const RobotLocation* robot1, const RobotLocation* robot2)
{
    return robot1->lastDisplacement > robot2->lastDisplacement;
}
void HalfCircleAlgorithm::findRobotMovementInputs()
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
    std::sort(userInputs.begin(),userInputs.end(), compereUserInputs);
    if(userInputs.size() == 0)
    {
        calculateDestinationsCenterOuter();
    }
    else
    {
        for(int i=0;i<userInputs.size();i++)
        {
            RobotLocation *currentRobot = userInputs.at(i);

            if(abs(outer1->x() - currentRobot->x) + abs(outer1->y() - currentRobot->y) < 100)
            {
                outer1->rx() = currentRobot->x;
                outer1->ry() = currentRobot->y;
            }
            else if(abs(outer2->x() - currentRobot->x) + abs(outer2->y() - currentRobot->y) < 100)
            {
                outer2->rx() = currentRobot->x;
                outer2->ry() = currentRobot->y;
            }
            else if(abs( distanceFromCenter(currentRobot->x, currentRobot->y) - distanceFromCenter(outer1->x(),outer1->y()) ) < 100)
            {
                radius = distanceFromCenter(currentRobot->x, currentRobot->y);
            }

            HalfCircleAlgorithm::calculateDestinationsCenterOuter();
        }
    }

}
void HalfCircleAlgorithm::calculateDestinationsOuterOuter()
{
    //this method uses two outer places of the circle, it calculates the center so the center-outer method can do the rest
    int deltaX = outer2->x() - outer1->x();
    int deltaY = outer2->y() - outer1->y();
    center->rx() = outer1->x() + deltaX / 2;
    center->ry() = outer1->y() + deltaY / 2;
    calculateDestinationsCenterOuter();
}
void HalfCircleAlgorithm::calculateDestinationsCenterOuter()
{
    //calculate center
    //calcute distance between outer1 and outer2
    int deltaX = outer2->rx() - outer1->rx();
    int deltaY = outer2->ry() - outer1->ry();
    int distance = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C
    int halfDistance = distance/2;

    int currentRadius = radius;
    if(halfDistance >= radius)
    {
        currentRadius = halfDistance;
    }

    //calculate the height of the line in the circle
    int lineHight = sqrt(currentRadius*currentRadius - halfDistance*halfDistance);
    qDebug("radius %d, halfdistance %d, lineheight %d",currentRadius,halfDistance,lineHight);
    double lineAngle = atan2(deltaY,deltaX);

    int lineMiddleX = cos(lineAngle) * halfDistance;
    int lineMiddleY = sin(lineAngle) * halfDistance;

    center->rx() = outer1->x() + lineMiddleX - cos(lineAngle+0.5*M_PI) * lineHight;
    center->ry() = outer1->y() + lineMiddleY - sin(lineAngle+0.5*M_PI) * lineHight;

    //begin angle
    deltaX = outer1->rx() - center->rx();
    deltaY = outer1->ry() - center->ry();
    double beginAngle = atan2(deltaY, deltaX);

    //end angle
    deltaX = outer2->rx() - center->rx();
    deltaY = outer2->ry() - center->ry();
    double endAngle = atan2(deltaY, deltaX);

    while(beginAngle < 0)
    {
        beginAngle += 2*M_PI;
        endAngle += 2*M_PI;
    }
    while(endAngle <= beginAngle)
    {
        endAngle += 2*M_PI;
    }
    CircleAlgorithm::calculateDestinationsCenterOuter(beginAngle,endAngle,true);
}
