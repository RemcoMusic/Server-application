#include <robotlocation.h>
QRectF RobotLocation::boundingRect() const
{
    return QRectF(0,0,2*globalSettings.botDiameter,2*globalSettings.botDiameter);
}

void RobotLocation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x,y);
    QRectF rect = boundingRect();
        QBrush brush(Qt::black);
        QPen pen(Qt::red);
        pen.setWidth(1);
        QFont f;

        double d = globalSettings.botDiameter;

        painter->translate(0.5*d,0.5*d);
        painter->rotate(angle);
        painter->translate(-0.5*d,-0.5*d);

        painter->setPen(pen);
        painter->setBrush(brush);

        painter->drawEllipse(0,0,d,d);

        brush.setColor(myColor);//statusColor
        painter->setBrush(brush);
        double p = 0.1; //value
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(Qt::black);//statusColor
        painter->setBrush(brush);
        p = 0.2;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(Qt::red);//statusColor
        painter->setBrush(brush);
        p = 0.45;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(Qt::red);//statusColor
        painter->setBrush(brush);
        double v =0.01;
        painter->drawRect(d/2-d*v,0,2*d*v,0.5*d);

//        for(int i = 0;i<=5;i++)
//        {

//            painter->drawArc(0,100-10*i,20*i,20*i,(-70)*16,(140)*16);


//        }


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
void RobotLocation::setRotation(int r){
    angle = r;
}
