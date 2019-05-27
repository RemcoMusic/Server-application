#include "swarmalgorithms.h"


SwarmAlgorithms::SwarmAlgorithms()
{

}
void SwarmAlgorithms::update()
{        
    QListIterator<SwarmAlgorithmBase*> i(swarmAlgorithmsSettings.activeAlgorithms);
    while (i.hasNext())
    {
        i.next()->update();
    }
    emit algoritmFinished();
}
