#pragma once

#include "linearmotionalgorithms.h"
#include "swarmalgorithmssettings.h"
#include "math.h"

class RectangleAlgorithm : public LinearMotionAlgorithms
{
public:
    RectangleAlgorithm();
    void update();
    QPoint *point1 = new QPoint(200,200);
    QPoint *point2 = new QPoint(800,800);
protected:
    void inputValidation();
    void calculatePoints();
    void calculateDestination();
    void findRobotMovementInputs();
};
