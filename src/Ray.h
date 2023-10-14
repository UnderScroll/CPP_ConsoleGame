#pragma once
#include <vector>

#include "Vector2.h"
#include "Collider.h"

namespace core {

class Ray {
public:
	struct CollisionInfo {
		Collider::CollisionType type;
		Vector2 point;
	};

	Ray(Vector2 position = Vector2(0, 0), Vector2 direction = Vector2(1, 0)): position(position) , direction(direction) {};

	Vector2 position;
	Vector2 direction;

	CollisionInfo cast(Vector2 a, Vector2 b); //Cast against segment
	std::vector<CollisionInfo> cast(Collider collider); //Cast against Collider
	CollisionInfo cast(Ray collider); //Cast against Ray

private:
	std::pair<const double, const double> ComputeCollisionConstant(Vector2& a, Vector2& b);
};

}