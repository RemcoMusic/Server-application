#ifndef SWARMALGORITHMS_H
#define SWARMALGORITHMS_H

#include <QObject>

#include <QTimer>
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;

class SwarmAlgorithms: public QObject
{
    Q_OBJECT
public:
    SwarmAlgorithms();

private slots:
    void update();
};

#endif // SWARMALGORITHMS_H
