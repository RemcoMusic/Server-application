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
    QPoint *point1 = new QPoint(1000,1000);
    QPoint *point2 = new QPoint(0,0);
private:
    void calculatePoints();
    void calculateDestination();
    void findRobotMovementInputs();
};

#endif // LINEALGORITHM_H
