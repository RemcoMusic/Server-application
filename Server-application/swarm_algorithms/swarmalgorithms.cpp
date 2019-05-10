#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(swarmAlgorithmsSettings.settingVariables.updateIntervalMs);
}
void SwarmAlgorithms::update()
{
    swarmAlgorithmsSettings.settingVariables.activeAlgorithm->update();
}
