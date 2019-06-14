#include "swarmalgorithmssettings.h"
//this time headers are included in the cpp to prevent include loops
#include "circlealgorithm.h"
#include "halfcirclealgorithm.h"
#include "linealgorithm.h"
#include "rectanglealgorithm.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;

SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
    anvailableAlgoritms << "RemcoAlgoritm"\
                           << "CircleAlgorirm"\
                        << "LineAlgoritm" << "halfCircleAlgorithm" << "RectangleAlgorithm";
}

void SwarmAlgorithmsSettings::runNewAlgortim(QString newAlgoritm, bool clearOthers)
{
    //clear the list
    if(clearOthers)
    {
        for(int i=0;i<activeAlgorithms.size();i++)
        {
            //system algorithms are algorithms that should not be deleted
            if(activeAlgorithms.at(i)->algorithmDiscription.systemAlgorithm == false)
            {
                delete activeAlgorithms.takeAt(i);
                i--;
            }
        }
    }


    //see which one is and add it it the list with active algiritms
    if(newAlgoritm == "CircleAlgorirm"){
        activeAlgorithms.append(new CircleAlgorithm());
    } else if(newAlgoritm == "LineAlgoritm"){
        activeAlgorithms.append(new LineAlgorithm());
    }
    else if(newAlgoritm == "halfCircleAlgorithm"){
        activeAlgorithms.append(new HalfCircleAlgorithm());
    }
    else if(newAlgoritm == "RectangleAlgorithm"){
        activeAlgorithms.append(new RectangleAlgorithm());
    }
}
