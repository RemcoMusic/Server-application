#include "algrorithmvisualisation.h"
#include "linearmotionalgorithms.h"
AlgrorithmVisualisation algorithmVisualisation;
AlgrorithmVisualisation::AlgrorithmVisualisation()
{

}
QRectF AlgrorithmVisualisation::boundingRect() const
{
    return QRectF(0,0,2*globalSettings.botDiameter,2*globalSettings.botDiameter);
}

void AlgrorithmVisualisation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::black);
    QPen pen(Qt::red);
    pen.setWidth(2);
    QFont f;
    painter->setPen(pen);
    painter->setBrush(brush);
    if(dynamic_cast<LinearMotionAlgorithms*>(swarmAlgorithmsSettings.activeAlgorithms.first()) != nullptr)
    {
        QListIterator<LinearMotionAlgorithms::Destination*> destinations( ((LinearMotionAlgorithms*)swarmAlgorithmsSettings.activeAlgorithms.first())->destinations);
        int index=0;
        while (destinations.hasNext())
        {
            LinearMotionAlgorithms::Destination *destination = destinations.next();
            const int size = 10;
            painter->drawLine(destination->x-size, destination->y-size, destination->x+size, destination->y+size);
            painter->drawLine(destination->x+size, destination->y-size, destination->x-size, destination->y+size);
            if(destination->robot!=nullptr)
            {
                painter->drawLine(destination->robot->x, destination->robot->y, destination->x, destination->y);
                painter->drawText(destination->robot->x ,destination->robot->y+30,QString::number(index));
            }
            index++;

        }
    }

}
