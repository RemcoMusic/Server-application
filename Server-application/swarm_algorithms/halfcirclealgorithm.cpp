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
    qSort(userInputs.begin(),userInputs.end(), compereUserInputs);
    if(userInputs.size() == 0)
    {
        calculateDestinationsCenterOuter();
    }
    else if(userInputs.size() == 1)
    {
        RobotLocation *currentRobot = userInputs.first();
        //first check if the robot is near the radius of the circle
//        if(abs(distanceFromCenter(outer1->x(),outer1->y()) - distanceFromCenter(currentRobot->x,currentRobot->y)) < 100)
//        {
//            outer1->rx() = currentRobot->x;
//            outer1->ry() = currentRobot->y;
//        }
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

        calculateDestinationsCenterOuter();
    }
    else
    {
//        RobotLocation *robot1 = userInputs.first();
//        RobotLocation *robot2 = userInputs.at(1);
//        outer1->rx() = robot1->x;
//        outer1->ry() = robot1->y;
//        outer2->rx() = robot2->x;
//        outer2->ry() = robot2->y;
//        calculateDestinationsOuterOuter();
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
    //begin angle
    int deltaX = outer1->rx() - center->rx();
    int deltaY = outer1->ry() - center->ry();
    double beginAngle = atan2(deltaY, deltaX);

    //end angle
    deltaX = outer2->rx() - center->rx();
    deltaY = outer2->ry() - center->ry();
    double endAngle = atan2(deltaY, deltaX);

    if(beginAngle < 0)beginAngle+=2*M_PI;
    if(endAngle < 0)endAngle+=2*M_PI;
    CircleAlgorithm::calculateDestinationsCenterOuter(std::min(beginAngle,endAngle), std::max(beginAngle,endAngle));
}
