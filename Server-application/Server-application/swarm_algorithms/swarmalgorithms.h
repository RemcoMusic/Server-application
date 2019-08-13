#ifndef SWARMALGORITHMS_H
#define SWARMALGORITHMS_H

#include <QObject>
#include <QtCore>
#include <QTimer>
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
class SwarmAlgorithms : public QObject
{
public:
    SwarmAlgorithms();

private:
    void update();
};

#endif // SWARMALGORITHMS_H
