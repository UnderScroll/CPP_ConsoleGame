#include "Level3.h"

#include "../Rectangle.h"

void core::levels::Level3::LoadLevel() {
	_lasers = {
	Laser(Vector2(35, 85), Vector2(1, 0))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0),
		Polygon({ Vector2(0, 50), Vector2(50, 57), Vector2(48, 64), Vector2(0, 87) }, false),
		Polygon({ Vector2(70, 100), Vector2(96, 66), Vector2(113, 76), Vector2(109, 87), Vector2(124, 100) }, false),
		Polygon({ Vector2(163, 69), Vector2(126, 61), Vector2(107, 66), Vector2(104, 55), Vector2(163, 38) }, false),
		Polygon({ Vector2(62, 29), Vector2(106, 28), Vector2(72, 41) }, true)
	};

	_rotatableElements = {
		Rectangle(Vector2(120, 15), Vector2(150, 19), Drawable::Color::BLUE),
		Rectangle(Vector2(15, 15), Vector2(35, 19), Drawable::Color::BLUE)
	};

	_sensor = Sensor(Rectangle(Vector2(127, 77), Vector2(137, 87), Drawable::Color::GREEN));

	Level::LoadLevel();
}