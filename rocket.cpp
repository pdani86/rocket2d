#include "rocket.h"

#include <algorithm>


Rocket::Rocket() {

}

void Rocket::iterate(float dt_us) {
    auto dt_sec = (dt_us / 1.0e6f);
    auto dir = Vec2D(std::cos(orientation), std::sin(orientation));  // TODO: thrust vectoring + torque

    Vec2D dv;
    auto m0 = getMass();
    if(throttle>=0.00001 && fuel >= 0.00001) {
        auto dFuel = maxFuelRate * throttle * dt_sec;
        dFuel = std::min(dFuel, fuel);
        fuel -= dFuel;
        if(fuel<0.0f) fuel = 0.0f;
        auto dm = dFuel * fuelMassPerUnit;
        auto mf = m0 - dm;
        dv = dir * maxEngineIsp * static_cast<float>(std::log(m0/mf));
    }

    velocity += dv;
    pos += velocity * dt_sec;

    auto turnTorquePercControl = turnTorquePerc;
    if(rotationDampener && std::abs(angular_speed)>0.00001f) {
        turnTorquePercControl = (angular_speed<0.0f)?(1.0f):(-1.0f);
    }

    angular_speed += turnMaxTorque * turnTorquePercControl / moment_of_inertia * dt_sec;

    rotateAroundCenterOfMass(angular_speed * dt_sec);
}

float Rocket::clampRad(float r) {
    auto nFull = std::floor((r + M_PI) / (2.0*M_PI));
    return r - nFull * 2.0 * M_PI;
}

void Rocket::rotateAroundCenterOfMass(float rad) {
    auto centerToNoseOrigo = (Vec2D(0.0f, 0.0f) - getCenterOfMassLocal()).rotated(orientation);
    auto globCenter = pos - centerToNoseOrigo;

    orientation += rad;
    pos = globCenter + centerToNoseOrigo.rotated(rad);
    orientation = clampRad(orientation);
    // TODO: clamp orientation [-pi, pi]
}
