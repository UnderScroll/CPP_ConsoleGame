#pragma once
#include "../Level.h"
#include "../Rectangle.h"
#include "../Console.h"

namespace core::levels {

class Level1 :
	public Level
{
public:
	Level1() {
		_movableElements = {
			Rectangle(50,80),
			Polygon({Vector2(-10, -10), Vector2(10, -10), Vector2(0, 10)}, true),
		};

		_staticNonReflectivesElements = {
		};

		_staticReflectivesElements = {
			Polygon({Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100)}, true),
		};

		_lasers = {
			Laser(Vector2(10, 10), Vector2(0.5, 0.5)),
		};

		_levelName = "First trials";
	}
};

}


