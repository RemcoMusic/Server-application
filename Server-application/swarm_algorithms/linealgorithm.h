#ifndef LINEALGORITHM_H
#define LINEALGORITHM_H

#include "linearmotionalgorithms.h"
#include "math.h"
#include "swarmalgorithmssettings.h"

extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;

class LineAlgorithm : public LinearMotionAlgorithms
{
public:
    LineAlgorithm();
    void update();
    QPoint *point1 = new QPoint(800,700);
    QPoint *point2 = new QPoint(100,200);
private:
    void calculatePoints();
    void calculateDestination();
};

#endif // LINEALGORITHM_H
