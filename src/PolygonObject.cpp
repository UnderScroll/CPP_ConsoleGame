#include "PolygonObject.h"

#include <cmath>

#include "Drawable.h"

void PolygonObject::Draw()
{
	for (int i = 0;i < _rotated_points.size()-((_isClosed)?0:1);++i) {
		Vector2 currentPoint = GetPosition() + _rotated_points[i];
		Vector2 nextPoint = GetPosition() + _rotated_points[(i<_rotated_points.size()-1)?i + 1:0];
		
		Drawable::ProcessLine(currentPoint, nextPoint,_color);
	}
}

void PolygonObject::RotateToRadians(float targetAngle)
{
	GameObject::RotateToRadians(targetAngle);
	_rotated_points.clear();
	for(Vector2 point:_points)
	{
		_rotated_points.push_back(point.RotateByRadians(GetRotationInRadians()));
	}
}
