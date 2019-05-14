#ifndef GRAPHICBOT_H
#define GRAPHICBOT_H
#include <globalsettings.h>

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>

class GraphicBot: public QGraphicsItem
{
public:
    GraphicBot();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRotation(int d);
    void setLocation(int x, int y);
    void setColor(QColor newColor);

private:
    int angle;
    int botSizeX;
    int botSizeY;
    int x;
    int y;
    QColor myColor;



};




#endif // GRAPHICBOT_H
