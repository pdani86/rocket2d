#ifndef ROCKETGRAPHICS_H
#define ROCKETGRAPHICS_H

#include <QGraphicsItemGroup>

#include "rocket.h"

class RocketGraphics : public QGraphicsItemGroup
{
public:
    RocketGraphics();
    void update(const Rocket& rocket);
    QGraphicsItemGroup* flame = nullptr;
    QGraphicsLineItem* flameLineLeft = nullptr;
    QGraphicsLineItem* flameLineRight = nullptr;

    float rocketWidth = 10.0;
    float rocketNoseHeight = 10.0;
    float rocketTankHeight = 40.0;
    float rocketEngineHeight = 10.0;

    float flameWk = 0.8;
    float flameMinHeight = 2.0;
    float flameMaxHeight = 20.0;
};

#endif // ROCKETGRAPHICS_H
