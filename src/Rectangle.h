#pragma once
#include "Polygon.h"

namespace core {

class Rectangle :
    public Polygon
{
public:
    Rectangle();
    Rectangle(Vector2 pointA, Vector2 pointB, Drawable::Color color = Drawable::Color::WHITE);
    Rectangle(float width, float height, Drawable::Color color = Drawable::Color::WHITE);
    Rectangle(Vector2 pointA, float width, float height, Drawable::Color color = Drawable::Color::WHITE);
};

}