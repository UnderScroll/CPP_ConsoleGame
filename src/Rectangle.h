#pragma once
#include "Polygon.h"

namespace core {

class Rectangle :
    public Polygon
{
public:
    Rectangle();
    Rectangle(Vector2 pointA, Vector2 pointB, Drawable::Color color = Drawable::Color::WHITE);
    Rectangle(double width, double height, Drawable::Color color = Drawable::Color::WHITE);
    Rectangle(Vector2 pointA, double width, double height, Drawable::Color color = Drawable::Color::WHITE);
};

}