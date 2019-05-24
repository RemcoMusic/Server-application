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
    QPoint *point1 = new QPoint(500,500);
    QPoint *point2 = new QPoint(800,500);
private:
    void calculatePoints();
};

#endif // CIRCLEALGORITHM_H
