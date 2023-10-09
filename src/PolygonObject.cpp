#include "PolygonObject.h"

#include <cmath>

#include "Drawable.h"
#include "Application.h"

std::shared_ptr<PolygonObject> PolygonObject::CreateRectangle(float x, float y, float width, float height, int color)
{
	return PolygonObject::CreatePolygon(RectangleConstructor(x, y, width, height, color));
}

std::shared_ptr<PolygonObject> PolygonObject::CreateLine(float x, float y, float length, int color)
{
	return PolygonObject::CreatePolygon(LineConstructor(x, y, length, color));
}

std::shared_ptr<PolygonObject> PolygonObject::CreateLine(float x1, float y1, float x2, float y2, int color)
{
	return PolygonObject::CreatePolygon(LineConstructor(x1, y1, x2, y2, color));
}

std::shared_ptr<PolygonObject> PolygonObject::CreatePolygon()
{
	return PolygonObject::CreatePolygon(std::vector<Vector2>(), 0x0007, true);
}

//TODO : Consider using a template defined in GameObject.h ?
std::shared_ptr<PolygonObject> PolygonObject::CreatePolygon(std::vector<Vector2> points, bool isClosed, int color, float alpha)
{
	return PolygonObject::CreatePolygon(PolygonObject(points, isClosed, color, alpha));
}

std::shared_ptr<PolygonObject> PolygonObject::CreatePolygon(const PolygonObject polygon_object)
{
	std::shared_ptr<PolygonObject> ptr = std::make_shared<PolygonObject>(polygon_object);
	Application::AddGameObject(ptr);
	return ptr;
}

PolygonObject PolygonObject::RectangleConstructor(float x, float y, float width, float height, int color)
{
	std::vector<Vector2> points;
	points.push_back(Vector2(-0.5f * width, -0.5f * height));
	points.push_back(Vector2(0.5f * width, -0.5f * height));
	points.push_back(Vector2(0.5f * width, 0.5f * height));
	points.push_back(Vector2(-0.5f * width, 0.5f * height));
	auto rectangle = PolygonObject(points, true, color, 1);
	rectangle.SetLocalPosition(Vector2(x, y));
	return rectangle;
}

PolygonObject  PolygonObject::LineConstructor(float x, float y, float length, int color)
{
	std::vector<Vector2> points;
	points.push_back(Vector2(-0.5f * length, 0));
	points.push_back(Vector2(0.5f * length, 0));
	auto line = PolygonObject(points, false, color, 1);
	line.SetLocalPosition(Vector2(x, y));
	return line;
}

PolygonObject PolygonObject::LineConstructor(float x1, float y1, float x2, float y2, int color)
{
	Vector2 startPoint(x1, y1);
	Vector2 endPoint(x2, y2);
	Vector2 middlePoint = startPoint + 0.5 * (endPoint - startPoint);
	float magnitude = (endPoint - startPoint).Magnitude();

	float angle = atan2(y2 - y1, x2 - x1) + PI_F / 2; //The angle that the line is facing
	auto line = LineConstructor(middlePoint._x, middlePoint._y, magnitude, color);
	line.RotateToRadians(angle);
	return line;
}


// Herite via GameObject

inline void PolygonObject::Draw()
{
	GameObject::Draw();
	for (unsigned long long i = 0; i < _computedPoints.size() - ((_isClosed) ? 0 : 1); ++i)
	{
		Vector2 currentPoint = GetWorldPosition() + (_computedPoints[i]);
		Vector2 nextPoint = GetWorldPosition() + (_computedPoints[(i < _computedPoints.size() - 1) ? i + 1 : 0]);

		Drawable::ProcessLine(currentPoint, nextPoint, _color);
	}

	auto position = GetWorldPosition();
}

void PolygonObject::RotateToRadians(float targetAngle)
{
	GameObject::RotateToRadians(targetAngle);
	ComputePoints();
}

void PolygonObject::SetLocalScale(Vector2 targetScale)
{
	GameObject::SetLocalScale(targetScale);
	ComputePoints();
}

void PolygonObject::ComputePoints()
{
	_computedPoints.clear();
	for (Vector2 point : _points)
	{
		_computedPoints.push_back((GetWorldScale() * point).RotateByRadians(GetWorldRotationInRadians()));
	}
}
