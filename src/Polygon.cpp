#include "Polygon.h"

#include <cmath>
#include <algorithm>

#include "Drawable.h"
#include "Application.h"

namespace core {

void Polygon::Draw()
{
	GameObject::Draw();

	for (size_t i = 0; i < _rotated_points.size() - (_isClosed ? 1 : 0); ++i)
	{
		Vector2 currentPoint = GetWorldPosition() + _rotated_points[i];
		Vector2 nextPoint = GetWorldPosition() + _rotated_points[(i + 1) % _rotated_points.size()];

		Drawable::DrawLine(currentPoint, nextPoint, _color);
	}

	auto position = GetWorldPosition();
}

void Polygon::RotateToRadians(float targetAngle)
{
	GameObject::RotateToRadians(targetAngle);
	for (size_t i = 0; i < _rotated_points.size(); ++i)
		_rotated_points[i] = _rotated_points[i].RotateByRadians(GetWorldRotationInRadians());
}

}

