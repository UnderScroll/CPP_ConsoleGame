#include "Rectangle.h"

#include <vector>

namespace core {

Rectangle::Rectangle(): Rectangle({ 0, 0 }, { 10, 10 }) {}

Rectangle::Rectangle(Vector2 pointA, Vector2 pointB, Drawable::Color color): Rectangle(pointA, pointB._x - pointA._x, pointB._y - pointA._y, color) {}

Rectangle::Rectangle(double width, double height, Drawable::Color color): Rectangle(Vector2(-width/2, -height/2), width, height, color) {}

Rectangle::Rectangle(Vector2 pointA, double width, double height, Drawable::Color color)
{
	this->_points.push_back(pointA);
	this->_points.push_back(pointA + Vector2(0, height));
	this->_points.push_back(pointA + Vector2(width, height));
	this->_points.push_back(pointA + Vector2(width, 0));
	this->_isClosed = true;
	_color = color;

	ComputePoints();
}

}


