#ifndef BALL_H
#define BALL_H

#include "objectsbase.h"

#include <QColor>



class Ball : public ObjectsBase
{
public:
    Ball();
    QColor myColor = Qt::yellow;
    int size = 50;//mm
};

#endif // BALL_H
