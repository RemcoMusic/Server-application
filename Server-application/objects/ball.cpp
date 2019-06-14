#include "ball.h"
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
    setPos(x-0.5*size,y-0.5*size);
    QPen pen(Qt::red);
    pen.setWidth(4);
    painter->setPen(pen);

    QPainterPath path;
    path.addEllipse(0,0,size,size);
    painter->fillPath(path, myColor);
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
