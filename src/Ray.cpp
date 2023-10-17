#include "Ray.h"

#include <exception>

namespace core {

std::vector<Ray::CollisionInfo> Ray::cast(Collider& collider) {

	std::vector<Vector2> colliderShapePoints = collider._collisionShape._computedPointsWorldPositions;
	std::vector<CollisionInfo> collisionInfos = std::vector<CollisionInfo>(colliderShapePoints.size());

	for (size_t i = 0; i < colliderShapePoints.size() - 1; ++i) {
		CollisionInfo info = cast(colliderShapePoints[i], colliderShapePoints[(i + 1)]);
		if (info.hasCollided) {
			info.collider = &collider;
			collisionInfos.push_back(info);
		}
	}
	if (collider._collisionShape._isClosed) {
		CollisionInfo info = cast(colliderShapePoints[colliderShapePoints.size() - 1], colliderShapePoints[0]);
		if (info.hasCollided) {
			info.collider = &collider;
			collisionInfos.push_back(info);
		}
	}

	return collisionInfos;
}

std::pair<const double, const double> Ray::ComputeCollisionConstant(Vector2& a, Vector2& b)
{
	//Constants that are needed two times
	const double c1 = a._x - b._x;
	const double c2 = a._y - b._y;
	const double c3 = a._x - _position._x;
	const double c4 = a._y - _position._y;
	const double c5 = _position._x - (_position._x + _direction._x);
	const double c6 = _position._y - (_position._y + _direction._y);

	const double denominator = c1 * c6 - c2 * c5;

	if (denominator == 0) //Checks null divider
		throw std::exception("Denominator was null, div by zero");

	const double t = (c3 * c6 - c4 * c5) / denominator;
	const double u = -(c1 * c4 - c2 * c3) / denominator;

	return std::pair<const double, const double>(t, u);
}


Ray::CollisionInfo Ray::cast(Vector2 a, Vector2 b) {
	CollisionInfo info;
	std::pair<double, double> constants;

	try {
		constants = ComputeCollisionConstant(a, b);
	}
	catch (std::exception e) {
		info.hasCollided = false;
		return info;
	}

	const double& t = constants.first;
	const double& u = constants.second;

	//If there is collision
	if (t > 0 && t < 1 && u > 0) {
		info.hasCollided = true;
		info.collisionSurface = { a, b };
		info.point = Vector2(a._x + t * (b._x - a._x), a._y + t * (b._y - a._y));
	}
	else
		info.hasCollided = false;

	return info;
}

Ray::CollisionInfo Ray::cast(Ray& ray) {
	CollisionInfo info;
	std::pair<double, double> constants;

	Vector2 rayBPoint = Vector2(ray._position._x + ray._direction._x, ray._position._y + ray._direction._y);

	try {
		constants = ComputeCollisionConstant(ray._position, rayBPoint);
	}
	catch (std::exception e) {
		info.hasCollided = false;
		return info;
	}

	const double& t = constants.first;
	const double& u = constants.second;

	//If there is collision
	if (t > 0 && u > 0) {
		info.hasCollided = true;
		info.collisionSurface = { ray._position, rayBPoint };
		info.point = Vector2(ray._position._x + t * (rayBPoint._x - ray._position._x), ray._position._y + t * (rayBPoint._y - ray._position._y));
	}
	else
		info.hasCollided = false;
	
	return info;
}

}