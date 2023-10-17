#include "Level1.h"

#include "../MovableObject.h"
#include "../MovableObjectButton.h"

void core::levels::Level1::LoadLevel() {
	_lasers = {
		Laser(Vector2(10, 10), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(50, 50), Vector2(60, 50), Vector2(60, 60), Vector2(50, 60) }, true)
	};

	_staticReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(WIDTH/2, 0), Vector2(WIDTH/2, 100), Vector2(0, 100) }, true, Drawable::WHITE,0)
	};
	
	_movableElements = {
		Polygon({ Vector2(0, 0), Vector2(10, 0), Vector2(10, 10), Vector2(0, 10) }, true)
	};

	_sensor = Sensor(Polygon({ Vector2(50, 10), Vector2(60, 10), Vector2(60, 20), Vector2(50, 20) }, true));


	Level::LoadLevel();
}