#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{
<<<<<<< HEAD
    QTimer *timer = new QTimer();
=======
    QTimer *timer = new QTimer(this);
>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(swarmAlgorithmsSettings.settingVariables.updateIntervalMs);
}
void SwarmAlgorithms::update()
{
    swarmAlgorithmsSettings.settingVariables.activeAlgorithm->update();
}
