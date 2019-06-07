#include "swarmalgorithmssettings.h"
#include "circlealgorithm.h"
#include "halfcirclealgorithm.h"
#include "linealgorithm.h"
#include "moveshapealgorithm.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;

SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
    anvailableAlgoritms << "RemcoAlgoritm"\
                           << "CircleAlgorirm"\
                        << "LineAlgoritm" << "halfCircleAlgorithm";
}

void SwarmAlgorithmsSettings::runNewAlgortim(QString newAlgoritm, bool clearOthers)
{
    //as of this time only one algoritm is allowed
    //clear the list
    if(clearOthers)
    {
        for(int i=0;i<activeAlgorithms.size();i++)
        {
            if(activeAlgorithms.at(i)->algorithmDiscription.systemAlgorithm == false)
            {
                delete activeAlgorithms.takeAt(i);
                i--;
            }
        }
    }


    //activeAlgorithms.clear();

    //see which one is and add it it the list with active algiritms
    if(newAlgoritm == "CircleAlgorirm"){
        activeAlgorithms.append(new CircleAlgorithm());
    } else if(newAlgoritm == "LineAlgoritm"){
        activeAlgorithms.append(new LineAlgorithm());
    }
    else if(newAlgoritm == "halfCircleAlgorithm"){
        activeAlgorithms.append(new HalfCircleAlgorithm());
    }
}
