#ifndef MOVESHAPEALGORITHM_H
#define MOVESHAPEALGORITHM_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "robotlocationmanager.h"
class MoveShapeAlgorithm : public SwarmAlgorithmBase

{
public:
    MoveShapeAlgorithm();
    void update();
};

#endif // MOVESHAPEALGORITHM_H
