#ifndef SWARMALGORITHMBASE_H
#define SWARMALGORITHMBASE_H

#include <QObject>

class SwarmAlgorithmBase
{
public:
    SwarmAlgorithmBase();
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
    ~SwarmAlgorithmBase();
>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
>>>>>>> ddf24cb3b641b767ea2ce7c3a6f6de85cb22d08d
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
<<<<<<< HEAD
=======

>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
>>>>>>> ddf24cb3b641b767ea2ce7c3a6f6de85cb22d08d
};

#endif // SWARMALGORITHMBASE_H
