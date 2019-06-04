#include "swarmalgorithmssettings.h"
#include "circlealgorithm.h"
#include "halfcirclealgorithm.h"
#include "linealgorithm.h"
#include "moveshapealgorithm.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;

SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{

   // activeAlgorithms.append(new LineAlgorithm());


    anvailableAlgoritms << "CircleAlgorirm"\
                           << "aap"\
                        << "LineAlgoritm" << "halfCircleAlgorithm";
}

void SwarmAlgorithmsSettings::runNewAlgortim(QString newAlgoritm)
{
    //as of this time only one algoritm is allowed
    //clear the list
    if(activeAlgorithms.size() > 0){

        delete(activeAlgorithms.takeAt(0));
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
