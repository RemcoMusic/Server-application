#include "userinputfunctions.h"
UserInputFunctions::UserInputFunctions()
{

}
static bool compereUserInputs(const Object* object1, const Object* object2)
{
    const RobotLocation* robot1 = dynamic_cast<const RobotLocation*>(object1);
    const RobotLocation* robot2 = dynamic_cast<const RobotLocation*>(object2);
    if(robot1 && robot2)return false;
    return robot1->lastDisplacement > robot2->lastDisplacement;
}
void UserInputFunctions::findRobotMovementInputs(QList<RobotLocation*>& swarmRobots)
{
    QListIterator<RobotLocation*> i(swarmRobots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->userInput)
        {
            userInputs.append(currentRobot);
            qDebug("added robot");
        }
    }
    std::sort(userInputs.begin(),userInputs.end(), compereUserInputs);
}
void UserInputFunctions::findObjectInputs()
{
    QListIterator<Object*> i(locationManager.objects);
    while (i.hasNext())
    {
        Object *currentObject = i.next();
        Ball* ball = dynamic_cast<Ball*>(currentObject);
        if(ball != nullptr)
        {
            if((ball->type == Ball::Type::REAL)||(swarmAlgorithmsSettings.algorithmAllowSimulatedObject))
            {
                userInputs.append(currentObject);
            }
        }
    }
}
void UserInputFunctions::constrainPoint(QPoint *point, int xMin, int yMin, int xMax, int yMax)
{
    point->rx() = std::max(xMin, point->x());
    point->ry() = std::max(yMin, point->y());
    point->rx() = std::min(xMax, point->x());
    point->ry() = std::min(yMax, point->y());
}
