#include "rocketgraphics.h"

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>


RocketGraphics::RocketGraphics()
{

    auto flameHeightDiff = flameMaxHeight - flameMinHeight;

    auto* rocketGraphicsItem = this;

    auto xLeft = -rocketWidth/2.0;
    auto xRight = rocketWidth/2.0;
    (new QGraphicsLineItem(0.0, 0.0, xLeft, -rocketNoseHeight))->setParentItem(rocketGraphicsItem);
    (new QGraphicsLineItem(0.0, 0.0, xRight, -rocketNoseHeight))->setParentItem(rocketGraphicsItem);
    (new QGraphicsRectItem(xLeft, -rocketNoseHeight, rocketWidth, -rocketTankHeight))->setParentItem(rocketGraphicsItem);
    auto tankBottomY = -rocketNoseHeight-rocketTankHeight;
    (new QGraphicsLineItem(0.0, tankBottomY, xLeft,tankBottomY - rocketEngineHeight))->setParentItem(rocketGraphicsItem);
    (new QGraphicsLineItem(0.0, tankBottomY, xRight, tankBottomY - rocketEngineHeight))->setParentItem(rocketGraphicsItem);

    flame = new QGraphicsItemGroup();
    flame->setParentItem(rocketGraphicsItem);


    auto engineBottomY = tankBottomY - rocketEngineHeight;

    (flameLineLeft = new QGraphicsLineItem(flameWk * xLeft, engineBottomY, 0.0, engineBottomY - flameMaxHeight))->setParentItem(flame);
    (flameLineRight = new QGraphicsLineItem(flameWk * xRight, engineBottomY, 0.0, engineBottomY - flameMaxHeight))->setParentItem(flame);
}

void RocketGraphics::update(const Rocket& rocket) {

    QTransform transform;
    transform.translate(rocket.pos.x, rocket.pos.y);
    transform.rotate((rocket.orientation - (M_PI*0.5)) * 180.0/M_PI);
    this->setTransform(transform);

    const bool flameVisible = (rocket.fuel > 0.0f && rocket.throttle > 0.0);

    auto tankBottomY = -rocketNoseHeight-rocketTankHeight;
    auto engineBottomY = tankBottomY - rocketEngineHeight;
    auto flameHeightDiff = flameMaxHeight - flameMinHeight;
    auto xLeft = -rocketWidth/2.0;
    auto xRight = rocketWidth/2.0;

    flame->setVisible(flameVisible);
    if(flameVisible) {
        auto flameHeight = flameMinHeight + flameHeightDiff * rocket.throttle;
        flameLineLeft->setLine(flameWk * xLeft, engineBottomY, 0.0, engineBottomY - flameHeight);
        flameLineRight->setLine(flameWk * xRight, engineBottomY, 0.0, engineBottomY - flameHeight);
    }
}
