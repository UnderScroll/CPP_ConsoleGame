#include "Polygon.h"

#include <cmath>
#include <algorithm>

#include "Drawable.h"

namespace core {

void Polygon::Draw()
{
	GameObject::Draw();

	for (size_t i = 0; i < _rotated_points.size() - (_isClosed ? 0 : 1); ++i)
	{
		Vector2 currentPoint = GetWorldPosition() + (_computedPoints[i]);
		Vector2 nextPoint = GetWorldPosition() + (_computedPoints[(i < _computedPoints.size() - 1) ? i + 1 : 0]);

		Drawable::DrawLine(currentPoint, nextPoint, _color);
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
	for (size_t i = 0; i < _points.size(); ++i)
	{
		_computedPoints[i]=(GetWorldScale() * _points[i]).RotateByRadians(GetWorldRotationInRadians());
	}
}
