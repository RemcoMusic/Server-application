#ifndef SWARMALGORITHMSSETTINGS_H
#define SWARMALGORITHMSSETTINGS_H

#include <QObject>
#include "swarmalgorithmbase.h"
class SwarmAlgorithmsSettings
{
public:
    SwarmAlgorithmsSettings();
    struct VisualisationVariables
    {
       QList<SwarmAlgorithmBase*> algorithms;
    }visualisationVariables;

    struct SettingVariables
    {
        SwarmAlgorithmBase *activeAlgorithm=nullptr;
        int updateIntervalMs=100;
    }settingVariables;
};
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
#endif // SWARMALGORITHMSSETTINGS_H
