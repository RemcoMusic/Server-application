#ifndef LINEARMOTIONALGORITHMS_H
#define LINEARMOTIONALGORITHMS_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "robotlocationmanager.h"

class LinearMotionAlgorithms : public SwarmAlgorithmBase
{
public:
    LinearMotionAlgorithms();
    QList<QPoint*> points;
};

#endif // LINEARMOTIONALGORITHMS_H
