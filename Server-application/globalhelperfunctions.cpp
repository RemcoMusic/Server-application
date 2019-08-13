#include "globalhelperfunctions.h"
    double map(double x, double x1, double x2, double y1, double y2)
    {
     return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
    }
double distanceBetweenPoints(int x1, int y1, int x2, int y2)
{
    int deltaX = x1 - x2;//pytagoras A
    int deltaY = y1 - y2;//pytagoras b
    return sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
}
double distanceBetweenPoints(Object* object1, Object* object2)
{
    int deltaX = object1->x - object2->x;//pytagoras A
    int deltaY = object1->y - object2->y;//pytagoras b
    return sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
}
bool isMoving(RobotLocation* robot)
{
    if(robot == nullptr)return false;
    if(distanceBetweenPoints(robot->x,robot->y,robot->destinationX, robot->destinationY) < 50)
    {
        return false;
    }
    if(robot->speed < 0.5)
    {
        return false;
    }
    return true;
}
void constrainObject(Object* object, int xMin, int yMin, int xMax, int yMax)
{
    object->x = std::max(xMin, object->x);
    object->y = std::max(yMin, object->y);
    object->x = std::min(xMax, object->x);
    object->y = std::min(yMax, object->y);
}
void constrainObjectInField(Object* object)
{
    int clearance = object->collisionRadius;
    constrainObject(object, clearance, clearance, globalSettings.fieldSizeX-clearance, globalSettings.fieldSizeY - clearance);
}
double calculateDeltaAngle(double angle1, double angle2)
{
    double deltaAngle = angle1 - angle2;
    if(deltaAngle > M_PI)
    {
        deltaAngle = deltaAngle - 2*M_PI;
    }
    if(deltaAngle < -M_PI)
    {
        deltaAngle = deltaAngle + 2*M_PI;
    }
    return deltaAngle;
}

