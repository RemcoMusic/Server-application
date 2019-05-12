#include "moveshapealgorithm.h"
#include "swarmalgorithmssettings.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;
SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
    visualisationVariables.algorithms.append(new MoveShapeAlgorithm());
<<<<<<< HEAD
=======

    settingVariables.activeAlgorithm = visualisationVariables.algorithms.first();
>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
}
