#pragma once

#include "circlealgorithm.h"
#include "linearmotionalgorithms.h"
#include "math.h"
#include "swarmalgorithmssettings.h"

class HalfCircleAlgorithm : public CircleAlgorithm
{
public:
    HalfCircleAlgorithm();
    void update();
private:
    void findRobotMovementInputs();
    void calculateDestinationsOuterOuter();
    void calculateDestinationsCenterOuter();
};
