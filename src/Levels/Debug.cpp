#include "Debug.h"

#include "../Rectangle.h"

void core::levels::Debug::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 65), Vector2(0.5, 0.5))
	};

	_movableElements = {
		Polygon({ Vector2(3, -4), Vector2(-4, 0), Vector2(3, 4) }, true, Drawable::Color::MAGENTA)
	};

	_sensorPos = Vector2(135, 15); 

	Level::LoadLevel();
}