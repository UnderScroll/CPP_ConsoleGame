#pragma once

#include "Polygon.h"

namespace core {

class Collider {
public:
	enum Type {
		Wall,
		Ray
	};

	Collider(Type collisionType = Type::Wall, bool isReflective = false);
	Collider(Polygon collisionShape, Type collisionType = Type::Wall, bool isReflective = false);

	Polygon collisionShape;
	Type type;
	bool isReflective;
};

}