#pragma once

#include "Polygon.h"

namespace core {

class Collider {
public:
	enum CollisionType {
		Null, //CollisionType not set
		Wall,
		Ray,
		OutOfBounds
	};

	Collider(CollisionType collisionType = CollisionType::Wall);
	Collider(Polygon collisionShape, CollisionType collisionType = CollisionType::Wall);

	Polygon collisionShape;
	CollisionType type;
};

}