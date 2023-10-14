#include "Ray.h"

#include <exception>

namespace core {

std::vector<Ray::CollisionInfo> Ray::cast(Collider collider) {

	std::vector<Vector2>& colliderShapePoints = collider.collisionShape._points;
	std::vector<CollisionInfo> collisionInfos;

	for (size_t i = 0; i < colliderShapePoints.size() - 1; ++i) {
		CollisionInfo info = cast(colliderShapePoints[i], colliderShapePoints[(i + 1)]);
		if (info.type != Collider::CollisionType::OutOfBounds) {
			info.type = collider.type;
			collisionInfos.push_back(info);
		}
	}
	if (collider.collisionShape._isClosed) {
		CollisionInfo info = cast(colliderShapePoints[colliderShapePoints.size() - 1], colliderShapePoints[0]);
		if (info.type != Collider::CollisionType::OutOfBounds) {
			info.type = collider.type;
			collisionInfos.push_back(info);
		}
	}

	return collisionInfos;
}

 std::pair<const double, const double> Ray::ComputeCollisionConstant(Vector2& a, Vector2& b)
{
	const double raySegX = (position._x + direction._x);
	const double raySegY = position._y + direction._y;

	const double denominator = (a._x - b._x) * (position._y - raySegY) - (a._y - b._y) * (position._x - raySegX);

	if (denominator == 0) //Checks null divider
		throw std::exception("Denominator was null, div by zero");

	const double t = ((a._x - position._x) * (position._y - raySegY) - (a._y - position._y) * (position._x - raySegX)) / denominator;
	const double u = -((a._x - b._x) * (a._y - position._y) - (a._y - b._y) * (a._x - position._x)) / denominator;

	return std::pair<const double, const double>(t, u);
}


Ray::CollisionInfo Ray::cast(Vector2 a, Vector2 b) {
	CollisionInfo info;

	try {

		std::pair<const double, const double> constants = ComputeCollisionConstant(a, b);
		const double& t = constants.first;
		const double& u = constants.second;

		//If there is collision
		if (t > 0 && t < 1 && u > 0) {
			info.type = Collider::CollisionType::Null;
			info.point = Vector2(a._x + t * (b._x - a._x), a._y + t * (b._y - a._y));
		}
		else
			info.type = Collider::CollisionType::OutOfBounds;
		return info;
	}
	catch (std::exception e) {
		info.type = Collider::CollisionType::OutOfBounds;
		return info;
	}

	
}

Ray::CollisionInfo Ray::cast(Ray ray) {
	CollisionInfo info;

	try {
		Vector2 rayBPoint = Vector2(ray.position._x + ray.direction._x, ray.position._y + ray.direction._y);
		std::pair<const double, const double> constants = ComputeCollisionConstant(ray.position, rayBPoint);
		const double& t = constants.first;
		const double& u = constants.second;

		//If there is collision
		if (t > 0 && u > 0) {
			info.type = Collider::CollisionType::Ray;
			info.point = Vector2(ray.position._x + t * (rayBPoint._x - ray.position._x), ray.position._y + t * (rayBPoint._y - ray.position._y));
		}
		else
			info.type = Collider::CollisionType::OutOfBounds;
		return info;
	}
	catch (std::exception e) {
		info.type = Collider::CollisionType::OutOfBounds;
		return info;
	}

}

}