#include "Level1.h"

#include "../MovableObject.h"
#include "../MovableObjectButton.h"

void core::levels::Level1::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 15), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(163, 0), Vector2(163, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0)
	};

	_staticReflectivesElements = {
	};
	
	_movableElements = {

	};

	Polygon sensorShape = Rectangle(Vector2(130, 10), Vector2(140, 20));
	sensorShape._color = Drawable::Color::GREEN;
	_sensor = Sensor(sensorShape);

	Level::LoadLevel();
}