#pragma once

#include <QObject>
#include "globalsettings.h"
#include "swarmalgorithmssettings.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
class AlgrorithmVisualisation: public QGraphicsItem
{
public:
    AlgrorithmVisualisation();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
extern AlgrorithmVisualisation algorithmVisualisation;
