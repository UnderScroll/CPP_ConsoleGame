#include "Rectangle.h"

#include <vector>

namespace core {

Rectangle::Rectangle(): Rectangle({ 0, 0 }, { 10, 10 }) {}

Rectangle::Rectangle(Vector2 pointA, Vector2 pointB, Drawable::Color color): Rectangle(pointA, pointB._x - pointA._x, pointB._y - pointA._y, color) {}

Rectangle::Rectangle(float width, float height, Drawable::Color color): Rectangle(Vector2(-width/2, -height/2), width, height, color) {}

Rectangle::Rectangle(Vector2 pointA, float width, float height, Drawable::Color color)
{
	this->SetLocalPosition(pointA+0.5*Vector2(width,height));

	this->_points.push_back(Vector2(-0.5*width, -0.5*height));
	this->_points.push_back(Vector2(0.5 * width, -0.5 * height));

	this->_points.push_back(Vector2(0.5 * width, 0.5 * height));
	this->_points.push_back(Vector2(-0.5 * width, 0.5 * height));

	this->_isClosed = true;
	_color = color;

	ComputePoints();
}

}


