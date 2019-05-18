#include "robotlocation.h"

RobotLocation::RobotLocation(RobotGroup *group)
{
    x = globalSettings.botDiameter/2;
    y = globalSettings.botDiameter/2;
}
void RobotLocation::print()
{
    if(type == RobotType::SIMULATED)
    {
        qDebug("robot at x=%d y=%d simulated",x,y);
    }
    else
    {
        qDebug("robot at x=%d y=%d real",x,y);
    }
}
