#ifndef SWARMALGORITHMSSETTINGS_H
#define SWARMALGORITHMSSETTINGS_H

#include <QObject>
#include "swarmalgorithmbase.h"
class SwarmAlgorithmsSettings
{
public:
    SwarmAlgorithmsSettings();

    QList<SwarmAlgorithmBase*> activeAlgorithms;

    int updateIntervalMs=100;
    int distanceBetweenRobots=150;//from center
};
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
#endif // SWARMALGORITHMSSETTINGS_H
