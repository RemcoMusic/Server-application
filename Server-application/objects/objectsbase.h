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
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
    int x;
    int y;
    int collisionRadius;
    long lastUpdated = 0;

    enum class Type
    {
        REAL = 1,
        SIMULATED=2
    }type;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // OBJECT_H
