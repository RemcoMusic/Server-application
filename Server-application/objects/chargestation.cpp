#include "chargestation.h"

ChargeStation::ChargeStation()
{
    collisionRadius = 100;
}

int ChargeStation::getDrivewayX()
{
    return x + cos(angle) * drivewayDistance;
}
int ChargeStation::getDrivewayY()
{
    return y + sin(angle) * drivewayDistance;
}

QRectF ChargeStation::boundingRect() const
{
    return QRectF(0,0,size,size);
}

void ChargeStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x-0.5*size,y-0.5*size);
    QRectF rect = boundingRect();
    QBrush brush(Qt::black);
    QPen pen(Qt::red);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRect(0,0,size,size);

}

void ChargeStation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "pressed!";
    Object::mousePressEvent(event);//call super class
}

void ChargeStation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    this->x = p.x();
    this->y = p.y();

}

void ChargeStation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
