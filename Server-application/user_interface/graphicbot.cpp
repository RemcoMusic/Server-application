#include "graphicbot.h"

QRectF GraphicBot::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void GraphicBot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
        QBrush brush(Qt::red);
        QPen pen(Qt::red);
        pen.setWidth(8);
        QFont f;


        painter->setPen(pen);

        for(int i = 0;i<=5;i++)
        {

            painter->drawArc(0,100-10*i,20*i,20*i,(-70)*16,(140)*16);


        }


//    painter->translate(100,100);
//    painter->rotate(angle);
//    painter->translate(-100,-100);
//    painter->drawImage(0,0,a);


//    QString i;
//    i.append("X = ");
//    i.append(QString::number(x));
//    i.append("  y = ");
//    i.append(QString::number(y));
//    painter->drawText(0,230, i);


}

void GraphicBot::setRotation(int d)
{
    angle = d;
}
