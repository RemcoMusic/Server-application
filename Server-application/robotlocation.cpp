#include "robotlocation.h"

RobotLocation::RobotLocation(RobotGroup *group)
{
    x = globalSettings.botDiameter/2;
    y = globalSettings.botDiameter/2;
    collisionRadius = globalSettings.botDiameter / 2;
    //setFlags(QGraphicsItem::ItemIsMovable);
}

RobotLocation::~RobotLocation()
{
    if(simulatedRobot != nullptr)
    {
        delete simulatedRobot;
    }
}

bool RobotLocation::isReady()
{
    if(sharedData.status == robotStatus::NORMAL){
        return true;
    }
    return false;
}
void RobotLocation::print()
{
    if(type == Object::Type::SIMULATED)
    {
        qDebug("robot at x=%d y=%d simulated",x,y);
    }
    else
    {
        qDebug("robot at x=%d y=%d real",x,y);
    }
}

void RobotLocation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Object::mousePressEvent(event);//call super class
}

void RobotLocation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    this->x = p.x();
    this->y = p.y();
}

void RobotLocation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
