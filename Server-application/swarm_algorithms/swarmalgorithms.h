#pragma once

#include <QObject>

#include <QTimer>
#include "algrorithmvisualisation.h"
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
//extern AlgrorithmVisualisation algorithmVisualisation;

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

