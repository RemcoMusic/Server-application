#include "ball.h"
//includes in the cpp to prevent include loops
#include "elasticball.h"
#include "locationmanager.h"
Ball::Ball()
{
    collisionRadius = 0;
}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0,size,size);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    constrainObjectInField(this);
    setPos(x-0.5*size,y-0.5*size);
    QPen pen(Qt::red);
    pen.setWidth(4);
    painter->setPen(pen);

    QColor color;
    if(BallColor == BallColor::ORANGE)
    {
        color = QColor("orange");
    }
    if(BallColor == BallColor::YELLOW)
    {
        color = Qt::yellow;
    }
    if(dynamic_cast<ElasticBall*>(this))
    {
        color = Qt::cyan;
    }
    QPainterPath path;
    path.addEllipse(0,0,size,size);
    painter->fillPath(path, color);
    for(int i=0;i<LocationManager::currentSelectedObjects.size();i++)
    {
        if(LocationManager::currentSelectedObjects.at(i) == this)
        {
            painter->drawPath(path);
        }
    }


}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Object::mousePressEvent(event);//call super class
}

void Ball::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    this->x = p.x();
    this->y = p.y();
    //qDebug() << x;

}

void Ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
