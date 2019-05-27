#ifndef CIRCLEALGORITHM_H
#define CIRCLEALGORITHM_H

#include "linearmotionalgorithms.h"
#include "math.h"
#include "swarmalgorithmssettings.h"

class CircleAlgorithm : public LinearMotionAlgorithms
{
public:
    CircleAlgorithm();
    void update();
    QPoint *center = new QPoint(500,500);
    QPoint *outer1 = new QPoint(200,500);
    QPoint *outer2 = new QPoint(800,500);

private:
    void calculateDestinationsCenterOuter();
    void calculateDestinationsOuterOuter();
    void calculateDestinationsOuterAngle();
};

#endif // CIRCLEALGORITHM_H
