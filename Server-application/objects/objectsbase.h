#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>


class Object: public QGraphicsItem
{
public:
    Object();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int x;
    int y;
    enum class Type
    {
        REAL = 1,
        SIMULATED=2
    }type;
};

#endif // OBJECT_H
