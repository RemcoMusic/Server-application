#ifndef SWARMBOTCOMMUNICATIONSETTINGS_H
#define SWARMBOTCOMMUNICATIONSETTINGS_H

#include <QObject>
#include "robotlocation.h"
#include "locationmanager.h"

class SwarmBotCommunicationSettings
{
public:
    SwarmBotCommunicationSettings();
    void resetIpList();
    void turnOffAllRobots();
    bool turnOffBots = false; // dirty solution
    struct VisualisationVariables
    {
        int amountOfBotsConnected=0;
    }visualisationVariables;

    struct SettingVariables
    {
        int updateRate=0;
    }settingVariables;
};
extern SwarmBotCommunicationSettings communicationSettings;
#endif // SWARMBOTCOMMUNICATIONSETTINGS_H
