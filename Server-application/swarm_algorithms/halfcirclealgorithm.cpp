#include "halfcirclealgorithm.h"

HalfCircleAlgorithm::HalfCircleAlgorithm()
{
    algorithmDiscription.name = "open circle algorithm";
    algorithmDiscription.discription = "bots drive in a open circle defined by balls or robot displacement";

}
void HalfCircleAlgorithm::update()
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
void HalfCircleAlgorithm::processUserInputs()
{
    bool centerUserInput = false;
    for(int i = 0;i<userInputs.size();i++)
    {
        Object *currentObject = userInputs.at(i);
        Ball* ball = dynamic_cast<Ball*>(currentObject);//use special color property of the ball
        if((ball == nullptr)||( ball->BallColor == Ball::BallColor::YELLOW))
        {
            if(abs(outer1->x() - currentObject->x) + abs(outer1->y() - currentObject->y) < 100)
            {
                outer1->rx() = currentObject->x;
                outer1->ry() = currentObject->y;
            }
            if(abs(outer2->x() - currentObject->x) + abs(outer2->y() - currentObject->y) < 100)
            {
                outer2->rx() = currentObject->x;
                outer2->ry() = currentObject->y;
            }
        }
        if((ball != nullptr)&&(ball->BallColor == Ball::BallColor::ORANGE))
        {
            if(abs( distanceFromCenter(currentObject->x, currentObject->y) - distanceFromCenter(outer1->x(),outer2->y())) < 100)
            {
                if(distanceBetweenPoints(outer1->x(),outer1->y(), currentObject->x,currentObject->y) > 100)
                {
                    if(distanceBetweenPoints(outer2->x(),outer2->y(), currentObject->x,currentObject->y) > 100)
                    {
                        centerUserInput = true;
                        radius = distanceFromCenter(currentObject->x, currentObject->y);
                    }
                }
            }
        }
    }
    if(centerUserInput)
    {
        calculateDestinationsCenterOuter();
    }
    else {
        calculateDestinationsOuterOuter();
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
