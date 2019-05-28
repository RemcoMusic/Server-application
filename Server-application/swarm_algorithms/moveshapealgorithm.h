#ifndef MOVESHAPEALGORITHM_H
#define MOVESHAPEALGORITHM_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "locationmanager.h"
class MoveShapeAlgorithm : public SwarmAlgorithmBase

{
public:
    MoveShapeAlgorithm();
    void update();
};

#endif // MOVESHAPEALGORITHM_H
