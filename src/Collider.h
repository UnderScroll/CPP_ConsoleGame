#pragma once

#include "Polygon.h"

namespace core {

class Collider {
public:
	enum Type {
		Wall,
		Ray
	};

	Collider(Polygon collisionShape, Type collisionType = Type::Wall, bool isReflective = false);

	Polygon _collisionShape;
	Type _type;
	bool _isReflective;
};

}