#pragma once

#include "linearmotionalgorithms.h"
#include "math.h"
#include "swarmalgorithmssettings.h"

class LineAlgorithm : public LinearMotionAlgorithms
{
public:
    LineAlgorithm();
    void update();
    QPoint *point1 = new QPoint(900,900);
    QPoint *point2 = new QPoint(0,0);
private:
    void calculatePoints();
    void calculateDestination();
    void findRobotMovementInputs();
};
