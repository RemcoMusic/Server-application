#include "objectsbase.h"

Object::Object()
{

}

QRectF Object::boundingRect() const
{
    return QRectF(0,0,1,1); // just a pixel.. might be painted in a later stage
}

void Object::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //not a real object.. so no painter
}
