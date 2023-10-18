#include "Level5.h"

#include "../Rectangle.h"

void core::levels::Level5::LoadLevel() {
	_lasers = {
		Laser(Vector2(140, 84), Vector2(-1, 0))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0),
		Polygon({ Vector2(50, 100), Vector2(60, 75), Vector2(70, 100) }, false),
		Polygon({ Vector2(116, 100), Vector2(122, 80), Vector2(142, 100) }, false),
		Polygon({ Vector2(70, 28), Vector2(108, 21), Vector2(150, 61), Vector2(96, 80), Vector2(62, 67), Vector2(39, 49), Vector2(68, 41), Vector2(66, 58), Vector2(100, 61), Vector2(108, 52), Vector2(100, 33), Vector2(74, 34) }, true)
	};

	_rotatableElements = {
		Rectangle(Vector2(5, 15), Vector2(35, 19), Drawable::Color::BLUE),
		Rectangle(Vector2(15, 70), Vector2(45, 74), Drawable::Color::BLUE)
	};

	_movableElements = {
		Polygon({ Vector2(-3, 4), Vector2(4, 0) , Vector2(-3, -4) }, true, Drawable::Color::MAGENTA),
		Rectangle(Vector2(-15, -2), Vector2(15, 2), Drawable::Color::MAGENTA)
	};

	_sensor = Sensor(Rectangle(Vector2(80, 40), Vector2(90, 50), Drawable::Color::GREEN));

	Level::LoadLevel();
}