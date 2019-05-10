#include "moveshapealgorithm.h"
#include "swarmalgorithmssettings.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;
SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
    visualisationVariables.algorithms.append(new MoveShapeAlgorithm());
}
