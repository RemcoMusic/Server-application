#pragma once

#include "swarmalgorithmssettings.h"
#include "linearmotionalgorithms.h"
#include "math.h"
#include "userinputfunctions.h"

class LineAlgorithm : public LinearMotionAlgorithms, public UserInputFunctions
{
public:
    LineAlgorithm();
    ~LineAlgorithm();
    void update();
    QPoint *point1 = new QPoint(800,800);
    QPoint *point2 = new QPoint(100,100);
protected:
    void inputValidation();
    void calculatePoints();
    void calculateDestination();
    void processUserInputs();
    void processUserAngleInputs();
};
