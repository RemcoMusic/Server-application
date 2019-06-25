#pragma once

#include "linearmotionalgorithms.h"
#include "swarmalgorithmssettings.h"
#include "math.h"
#include "userinputfunctions.h"
#include "globalsettings.h"

class TriangleAlgorithm : public LinearMotionAlgorithms, public UserInputFunctions
{
public:
    TriangleAlgorithm();
    ~TriangleAlgorithm();
    void update() override;
    QPoint *point1 = new QPoint(600,300);
    QPoint *point2 = new QPoint(900,550);
    QPoint *point3 = new QPoint(300,150);

protected:
    void inputValidation();
    void calculatePoints();
    void calculateDestination();
    void processUserInputs();
};

