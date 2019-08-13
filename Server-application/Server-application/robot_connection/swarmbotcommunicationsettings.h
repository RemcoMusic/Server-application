#ifndef SWARMBOTCOMMUNICATIONSETTINGS_H
#define SWARMBOTCOMMUNICATIONSETTINGS_H

#include <QObject>

class SwarmBotCommunicationSettings
{
public:
    SwarmBotCommunicationSettings();
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
