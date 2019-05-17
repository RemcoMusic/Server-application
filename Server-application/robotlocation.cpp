#include "robotlocation.h"

RobotLocation::RobotLocation(RobotGroup *group)
{
    location = new QPoint();
    location->setX(globalSettings.botDiameter/2);
    location->setY(globalSettings.botDiameter/2);
}
void RobotLocation::print()
{
    if(type == RobotType::SIMULATED)
    {
        qDebug("robot at x=%d y=%d simulated",location->x(),location->y());
    }
    else
    {
        qDebug("robot at x=%d y=%d real",location->x(),location->y());
    }
}
