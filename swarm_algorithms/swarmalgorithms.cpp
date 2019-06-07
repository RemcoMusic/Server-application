#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{

}
void SwarmAlgorithms::update()
{        
    robotDisplacementDetection.update();
    QListIterator<SwarmAlgorithmBase*> i(swarmAlgorithmsSettings.activeAlgorithms);
    while (i.hasNext())
    {
        i.next()->update();
    }
    robotDisplacementDetection.sync();
    emit algoritmFinished();
}
