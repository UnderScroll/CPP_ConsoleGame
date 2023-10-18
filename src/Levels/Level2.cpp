#include "Level2.h"

#include "../Rectangle.h"

void core::levels::Level2::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 15), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0),
		Polygon({ Vector2(70, 0), Vector2(90, 0), Vector2(90, 50), Vector2(70, 50) }, true)
	};

	_rotatableElements = {
		 Rectangle(Vector2(10, 90), Vector2(40, 94),Drawable::Color::LIGHT_BLUE)
	};

	_sensorPos = Vector2(135, 15);

	Level::LoadLevel();
}