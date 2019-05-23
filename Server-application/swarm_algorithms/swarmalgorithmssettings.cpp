#include "circlealgorithm.h"
#include "linealgorithm.h"
#include "moveshapealgorithm.h"
#include "swarmalgorithmssettings.h"
SwarmAlgorithmsSettings swarmAlgorithmsSettings;
SwarmAlgorithmsSettings::SwarmAlgorithmsSettings()
{
   activeAlgorithms.append(new CircleAlgorithm());
}
