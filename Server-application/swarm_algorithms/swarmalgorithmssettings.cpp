#include "moveshapealgorithm.h"
#include "swarmalgorithmssettings.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;
SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
    algorithms.append(new MoveShapeAlgorithm());

    activeAlgorithm = algorithms.first();
}
