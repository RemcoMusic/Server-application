#pragma once

#include <QObject>

#include "algrorithmvisualisation.h"
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

