#ifndef BALL_H
#define BALL_H

#include "objectsbase.h"
#include <QDebug>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include "globalhelperfunctions.h"



class Ball : public Object
{
public:
    Ball();
    enum class BallColor
    {
        YELLOW,
        ORANGE
    }BallColor;

    int size = 50;//mm

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // BALL_H
