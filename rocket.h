#ifndef ROCKET_H
#define ROCKET_H

#include "vec2d.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Rocket
{
public:
    Rocket();

    float getMass() const {return emptyMass + fuel * fuelMassPerUnit;}

    void iterate(float dt_us);
    void addMomentum(const Vec2D& dp) {velocity += dp * (1.0f/getMass());}
    void turn(float k) {if(k<-1.0) k = -1.0; if(k>1.0) k = 1.0; turnTorquePerc = k;}


public:
    //Vec2D getCenterOfMassLocal() const {return Vec2D(0.0f, -30.0f);}
    Vec2D getCenterOfMassLocal() const {return Vec2D(-30.0f, 0.0f);}
    Vec2D getCenterOfMassGlobal() const {return pos + getCenterOfMassLocal(); }
    void rotateAroundCenterOfMass(float rad);

    static float clampRad(float r);

public:
    Vec2D pos;
    Vec2D velocity;
    float orientation = M_PI / 2.0;
    float angular_speed = 0.0;


    float emptyMass = 10000.0;
    float fuel = 100000.0;
    float fuelTankCapacity = 100000.0;

    float engineAngle = 0.0;

    float maxEngineIsp = 3000.0; // m/s (ve)
    float fuelMassPerUnit = 1.0;
    float throttle = 0.0;
    float maxFuelRate = 1000.0; // 1/s

    float moment_of_inertia = 1.0;
    float turnMaxTorque = 1.0;
    float turnTorquePerc = 0.0;
    bool rotationDampener = false;
};

#endif // ROCKET_H
