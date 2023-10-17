#pragma once

#include "Polygon.h"

namespace core {

class Collider {
public:
	virtual ~Collider() {};

	enum Type {
		Wall,
		Sensor
	};

	Collider(Polygon collisionShape, Type collisionType = Type::Wall, bool isReflective = false);

	Polygon _collisionShape;
	Type _type;
	bool _isReflective;

	unsigned int chargeLevel = 0;
};

}