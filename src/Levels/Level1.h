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
			Polygon({Vector2(0, 0), Vector2(328, 0), Vector2(328, 124), Vector2(0, 124)}, true),
		};

		_lasers = {
			Laser(Vector2(10, 10), Vector2(0.5, 0.5)),
		};

		_levelName = "First trials";
	}
};

}


