#pragma once
#include "Collider.h"

namespace core{

/*
Sensor that the laser must light to end the level
*/
class Sensor
	: public Collider
{
public:
	Sensor(Polygon collisionShape = Polygon({Vector2(0, 0), Vector2(10, 0) , Vector2(10, 10) , Vector2(0, 10) }, true, Drawable::GREEN)) : Collider(collisionShape, Type::Sensor, false) {}
};

}