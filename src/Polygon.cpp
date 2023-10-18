#include "Polygon.h"

#include <cmath>
#include <algorithm>

#include "Drawable.h"

namespace core {

Vector2 Polygon::GetBoundingBox()
{
	ComputePoints();
	double minX = INFINITY;
	double minY = INFINITY;
	double maxX = -INFINITY;
	double maxY = -INFINITY;

	for (auto point : _computedPoints)
	{
		minX = std::min(minX, point._x);
		minY = std::min(minY, point._y);
		maxX = std::max(maxX, point._x);
		maxY = std::max(maxY, point._y);
	}

	return Vector2(maxX - minX, maxY - minY);
}

double Polygon::GetDiameter()
{
	Vector2 boundingBox = GetBoundingBox();
	double maxDiamater = boundingBox.Magnitude();
	for (auto point : _computedPoints)
	{
		maxDiamater = std::max(maxDiamater, (GetLocalPosition() + point).Magnitude());
	}

	return maxDiamater;
}

void Polygon::Draw()
{
	GameObject::Draw();

	if(_alpha<=0) return;

	if (_computedPoints.size() != _points.size())
	{
		ComputePoints();
	}

	if (_computedPoints.size() == 0)
		return;


	auto position = GetWorldPosition();

	for (size_t i = 0; i < _computedPoints.size() - (_isClosed ? 0 : 1); ++i)
	{
		Vector2 currentPoint = position+_computedPoints[i];
		Vector2 nextPoint = position+_computedPoints[(i < _computedPoints.size() - 1) ? i + 1 : 0];

		Drawable::DrawLine(currentPoint, nextPoint, _color,_alpha);
	}
}

void Polygon::RotateToRadians(double targetAngle)
{
	GameObject::RotateToRadians(targetAngle);
	ComputePoints();
}

void Polygon::SetLocalScale(Vector2 targetScale)
{
	GameObject::SetLocalScale(targetScale);
	ComputePoints();
}

void Polygon::OnCreationOver()
{
	GameObject::OnCreationOver();
	ComputePoints();
}

void Polygon::ComputePoints()
{
	if (_computedPoints.size() != _points.size())
		_computedPoints.resize(_points.size());

	for (size_t i = 0; i < _points.size(); ++i)
	{
		_computedPoints[i] = (GetWorldScale() * _points[i]).RotateByRadians(GetWorldRotationInRadians());
	}

	_computedPointsWorldPositions = _computedPoints;
	for (size_t i = 0; i < _computedPointsWorldPositions.size(); ++i) {
		_computedPointsWorldPositions[i] = GetWorldPosition() + _computedPoints[i];
	}
}

}