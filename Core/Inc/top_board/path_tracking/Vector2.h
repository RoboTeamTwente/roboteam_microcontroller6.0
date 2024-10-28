#ifndef VECTOR2_H
#define VECTOR2_H

#pragma once
#include <math.h>

class Vector2 {
public:
    double x;
    double y;

    Vector2(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2 &other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    double length() const {
        return sqrt(x * x + y * y);
    }

    double angle() const {
        return atan2(y, x);
    }
};


#endif // VECTOR2_H
