#pragma once

#include "linearmotionalgorithms.h"
#include "swarmalgorithmssettings.h"
#include "math.h"
#include "userinputfunctions.h"

class RectangleAlgorithm : public LinearMotionAlgorithms, public UserInputFunctions
{
public:
    RectangleAlgorithm();
    void update();
    QPoint *point1 = new QPoint(200,200);
    QPoint *point2 = new QPoint(700,700);
protected:
    void inputValidation();
    void calculatePoints();
    void calculateDestination();
    void processUserInputs();
};
