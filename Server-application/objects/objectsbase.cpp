#include "objectsbase.h"
#include "locationmanager.h"

#include <QGuiApplication>
Object::Object()
{

}

QRectF Object::boundingRect() const
{
    return QRectF(0,0,1,1); // just a pixel.. might be painted in a later stage
}

void Object::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        LocationManager::currentSelectedObjects.append(this);
        qDebug("shift pressed");
    }
    else {
        LocationManager::currentSelectedObjects.clear();
        LocationManager::currentSelectedObjects.append(this);

    }
}
void Object::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //not a real object.. so no painter
}
