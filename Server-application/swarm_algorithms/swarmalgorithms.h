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

public slots:
    void update();
signals:
    void algoritmFinished();
};

#endif // SWARMALGORITHMS_H
