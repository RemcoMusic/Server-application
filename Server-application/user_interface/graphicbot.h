#ifndef GRAPHICBOT_H
#define GRAPHICBOT_H


#include <QGraphicsItem>
#include <QPainter>

class GraphicBot: public QGraphicsItem
{
public:
    //graphicCompass();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRotation(int d);


private:
    int angle;
    int botSizeX;
    int botSizeY;


};




#endif // GRAPHICBOT_H
