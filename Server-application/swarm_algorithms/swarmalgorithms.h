#ifndef SWARMALGORITHMS_H
#define SWARMALGORITHMS_H

#include <QObject>
<<<<<<< HEAD
#include <QtCore>
#include <QTimer>
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
class SwarmAlgorithms : public QObject
{
public:
    SwarmAlgorithms();

private:
=======
#include <QTimer>
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;

class SwarmAlgorithms: public QObject
{
    Q_OBJECT
public:
    SwarmAlgorithms();

private slots:
>>>>>>> a082620c37a6e34ff5ddb202f8037fe7e4dd7d1f
    void update();
};

#endif // SWARMALGORITHMS_H
