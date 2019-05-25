#include "robotlocation.h"

RobotLocation::RobotLocation(RobotGroup *group)
{
    x = globalSettings.botDiameter/2;
    y = globalSettings.botDiameter/2;
    //setFlags(QGraphicsItem::ItemIsMovable);
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

double tempAngle;
void RobotLocation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("press");
    tempAngle = angle;
}

void RobotLocation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    this->x = p.x();
    this->y = p.y();
    this->angle = tempAngle;
}

void RobotLocation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
