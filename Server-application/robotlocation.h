//Swarmbotron application
//Rene Schouten
//5-2019
//this class represent a single robot of the swarm, it can be both simulated or real
#ifndef ROBOTLOCATION_H
#define ROBOTLOCATION_H

#include <QObject>
#include "robotgroup.h"

class RobotLocation
{
public:
    RobotLocation(RobotGroup *group = nullptr);
    int x = 0;
    int y = 0;
    int angle = 0;//degrees seen from the camera

    double batteryVoltage=7.4;

    int destinationX = 0;
    int destinationY = 0;

    RobotGroup* group = nullptr;
    enum class RobotType
    {
        REAL = 1,
        SIMULATED=2
    }type;
    void print();

};

#endif // ROBOTLOCATION_H
