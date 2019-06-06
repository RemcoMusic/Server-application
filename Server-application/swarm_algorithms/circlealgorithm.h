#pragma once

#include "linearmotionalgorithms.h"
#include "math.h"
#include "swarmalgorithmssettings.h"

class CircleAlgorithm : public LinearMotionAlgorithms
{
public:
    CircleAlgorithm();
    virtual void update();
    QPoint *center = new QPoint(500,500);
    QPoint *outer1 = new QPoint(250,500);
    QPoint *outer2 = new QPoint(750,500);
    QList<Object *> userInputs;

private:
    void findRobotMovementInputs();
protected:
    void processUserInputsCenterOuter();
    void processUserInputsOuterOuter();
    void findObjectInputs(bool simulated);

    int distanceFromCenter(int x, int y);
    void calculateDestinationsCenterOuter();
    void calculateDestinationsOuterOuter();
    void calculateDestinationsOuterAngle();
    void calculateDestinationsCenterOuter(double beginAngle, double endAngle, bool addExtra = false);

    void inputValidation();
};
