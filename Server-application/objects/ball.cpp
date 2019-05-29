#include "ball.h"

Ball::Ball()
{

}

QRectF Ball::boundingRect() const
{
    return QRectF(0,0,size,size);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x-0.5*size,y-0.5*size);
    QRectF rect = boundingRect();
    QBrush brush(myColor);
    QPen pen(Qt::red);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawEllipse(0,0,size,size);


}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "pressed!";
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
