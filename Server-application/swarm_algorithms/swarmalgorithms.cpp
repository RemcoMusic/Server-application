#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(swarmAlgorithmsSettings.updateIntervalMs);
}
void SwarmAlgorithms::update()
{
    swarmAlgorithmsSettings.activeAlgorithm->update();
}
