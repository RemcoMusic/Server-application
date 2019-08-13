#include "swarm_algorithms/moveshapealgorithm.h"

MoveShapeAlgorithm::MoveShapeAlgorithm()
{
    algorithmDiscription.name = "moving shape";
    algorithmDiscription.discription = "this is a test algorithm";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 10;
}
void MoveShapeAlgorithm::update()
{
    qDebug("update move shape algorithm");
}
