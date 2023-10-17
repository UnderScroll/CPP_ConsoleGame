#include "Level1.h"

void core::levels::Level1::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 65), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0)
	};

	_sensor = Sensor(Rectangle(Vector2(130, 10), Vector2(140, 20), Drawable::Color::GREEN));

	Level::LoadLevel();
}