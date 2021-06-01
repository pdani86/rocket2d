#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>

class Vec2D
{
public:
    Vec2D();
    Vec2D(float x, float y) : x(x), y(y) {}

    Vec2D operator+(const Vec2D& v) const {
        return Vec2D(x+v.x, y+v.y);
    }

    Vec2D operator-(const Vec2D& v) const {
        return Vec2D(x-v.x, y-+v.y);
    }

    Vec2D& operator+=(const Vec2D& v) {
        x+=v.x;
        y+=v.y;
        return *this;
    }

    Vec2D& operator-=(const Vec2D& v) {
        x-=v.x;
        y-=v.y;
        return *this;
    }

    Vec2D operator*(float k) const {return Vec2D(x*k, y*k);}

    float lengthSqr() const {return x*x+y*y;}
    float length() const {return std::sqrt(lengthSqr());}

    Vec2D rotated(float angleRadCCW) const {
        Vec2D result;
        auto C = std::cos(angleRadCCW);
        auto S = std::sin(angleRadCCW);
        result.x = x * C - y * S;
        result.y = x * S + y * C;
        return result;
    }

//private:
    float x = 0.0;
    float y = 0.0;
};


#endif // VEC2D_H
