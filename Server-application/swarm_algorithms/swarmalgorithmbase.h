#ifndef SWARMALGORITHMBASE_H
#define SWARMALGORITHMBASE_H

#include <QObject>

class SwarmAlgorithmBase
{
public:
    SwarmAlgorithmBase();
<<<<<<< HEAD
=======
    ~SwarmAlgorithmBase();
>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
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
<<<<<<< HEAD
=======

>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
};

#endif // SWARMALGORITHMBASE_H
