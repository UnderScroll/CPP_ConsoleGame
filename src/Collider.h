#pragma once

#include "Polygon.h"

namespace core {

/*
An object that can collide with a ray
*/
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