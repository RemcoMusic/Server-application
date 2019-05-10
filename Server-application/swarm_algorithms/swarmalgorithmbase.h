#ifndef SWARMALGORITHMBASE_H
#define SWARMALGORITHMBASE_H

#include <QObject>

class SwarmAlgorithmBase
{
public:
    SwarmAlgorithmBase();
    ~SwarmAlgorithmBase();
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
