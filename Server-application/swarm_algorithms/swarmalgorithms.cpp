#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{
    //add the charge algorithm to the active algorithm, the chargeAlgorthm is always present in the list
    swarmAlgorithmsSettings.activeAlgorithms.append(&chargeAlgorithm);
}
void SwarmAlgorithms::update()
{        
    doTheAlgoritm();
    emit algoritmFinished();
}
void SwarmAlgorithms::doTheAlgoritm(){
    robotDisplacementDetection.update();
    QListIterator<SwarmAlgorithmBase*> i(swarmAlgorithmsSettings.activeAlgorithms);
    while (i.hasNext())
    {
        i.next()->update();
    }
    robotDisplacementDetection.sync();
}
