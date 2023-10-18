#include "Level4.h"

#include "../Rectangle.h"

void core::levels::Level4::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 15), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0),
		Polygon({ Vector2(70, 0), Vector2(90, 0), Vector2(90, 50), Vector2(70, 50) }, true)
	};

	_movableElements = {
		Polygon({ Vector2(-3, 4), Vector2(4, 0) , Vector2(-3, -4) }, true, Drawable::Color::PURPLE)
	};

	_sensorPos = Vector2(135, 15);

	Level::LoadLevel();
}