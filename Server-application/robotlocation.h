//Swarmbotron application
//Rene Schouten
//5-2019
//this class represent a single robot of the swarm, it can be both simulated or real
#ifndef ROBOTLOCATION_H
#define ROBOTLOCATION_H

#include <QObject>

class RobotLocation
{
public:
    RobotLocation();
    int x = 0;
    int y = 0;
    int angle = 0;//degrees seen from the camera
    enum class RobotType
    {
        REAL = 1,
        SIMULATED=2
    }type;

};

#endif // ROBOTLOCATION_H
