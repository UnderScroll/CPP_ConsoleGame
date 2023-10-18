#include "Vector2.h"

namespace core {

Vector2 Vector2::RotateByRadians(double angle, Vector2 center) const
{
    double newX = cos(angle) * (_x - center._x) - sin(angle) * (_y - center._y) + center._x;
    double newY = sin(angle) * (_x - center._x) + cos(angle) * (_y - center._y) + center._y;
    return Vector2(newX, newY);
}

Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b)
{
    Vector2 copy(r_v2a);
    copy += r_v2b;
    return copy;
}

Vector2 operator+=(Vector2& r_v2a, Vector2 const& r_v2b)
{
    r_v2a._x += r_v2b._x;
    r_v2a._y += r_v2b._y;
    return r_v2a;
}

Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b)
{
    return Vector2(r_v2a._x - r_v2b._x, r_v2a._y - r_v2b._y);
}


Vector2 operator*(double const& number, Vector2 const& r_v2b)
{
    return Vector2(number * r_v2b._x, number * r_v2b._y);
}

Vector2 operator*(Vector2 const& r_v2a, double const& number)
{
    return Vector2(number * r_v2a._x, number * r_v2a._y);
}

Vector2 operator*(Vector2 const& r_v2a, Vector2 const& r_v2b)
{
    return Vector2(r_v2a._x * r_v2b._x, r_v2a._y * r_v2b._y);
}

bool Vector2::operator==(const Vector2& other) const
{
    return (_x == other._x && _y == other._y);;
}

double distSqrd(Vector2 a, Vector2 b) {
    return (b._x - a._x) * (b._x - a._x) + (b._y - a._y) * (b._y - a._y);
}
}