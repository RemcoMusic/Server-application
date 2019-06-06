#ifndef SWARMALGORITHMBASE_H
#define SWARMALGORITHMBASE_H

#include <QObject>
#include <robotgroup.h>

class SwarmAlgorithmBase
{
public:
    SwarmAlgorithmBase();

    ~SwarmAlgorithmBase();
    RobotGroup *robotGroup = nullptr;
    struct AlgorithmDiscription
    {
        QString name;
        QString discription;
        int minimalAmountOfBots;
        int maximalAmountOfBots;
        QString errorMessage;
        bool errorOccured=false;
    }algorithmDiscription;
    virtual void update()=0;

};

#endif // SWARMALGORITHMBASE_H
