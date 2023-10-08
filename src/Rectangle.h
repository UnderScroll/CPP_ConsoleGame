#pragma once
#include "Polygon.h"

namespace core {

class Rectangle :
    public Polygon
{
public:
    Rectangle();
    Rectangle(Vector2 pointA, Vector2 pointB);
    Rectangle(float width, float height);
    Rectangle(Vector2 pointA, float width, float height);
};

}