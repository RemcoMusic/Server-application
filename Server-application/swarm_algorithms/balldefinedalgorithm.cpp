#include "balldefinedalgorithm.h"

BallDefinedAlgorithm::BallDefinedAlgorithm()
{
    algorithmDiscription.name = "ball defined algorithm";
    algorithmDiscription.discription = "bots drive to balls";
}
void BallDefinedAlgorithm::update()
{
    LinearMotionAlgorithms::generateRobotList();
    LinearMotionAlgorithms::clearDestinations();
    QListIterator<Object*> i(locationManager.objects);
    while (i.hasNext())
    {
        Object *currentObject = i.next();
        Ball* ball = dynamic_cast<Ball*>(currentObject);
        if(ball != nullptr)
        {
            if((ball->type == Ball::Type::REAL)||(swarmAlgorithmsSettings.algorithmAllowSimulatedObject))
            {
                Destination* newDestination = new Destination;
                newDestination->x = ball->x;
                newDestination->y = ball->y;
                destinations.append(newDestination);
            }
        }
    }
    LinearMotionAlgorithms::update();

}
