#include "Level1.h"

#include "../MovableObject.h"
#include "../MovableObjectButton.h"

void core::levels::Level1::LoadLevel() {
	_lasers = {
		Laser(Vector2(10, 10), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		_lasers[0]._laserBase,
		Polygon({ Vector2(50, 50), Vector2(60, 50), Vector2(60, 60), Vector2(50, 60) }, true)
	};

	_staticReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true)
	};
	
	_movableElements = {
		Polygon({ Vector2(0, 0), Vector2(10, 0), Vector2(10, 10), Vector2(0, 10) }, true)
	};


	Level::LoadLevel();
}