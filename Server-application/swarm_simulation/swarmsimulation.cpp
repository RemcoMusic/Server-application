#include "swarmsimulation.h"

#include <swarmalgorithmbase.h>

SwarmSimulation::SwarmSimulation()
{

}

void SwarmSimulation::startSimulation()
{
qDebug() << "start simulation called" << endl;



// do stuff


emit simulationFinished();
}

