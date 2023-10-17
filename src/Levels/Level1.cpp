#include "Level1.h"

#include "../MovableObject.h"
#include "../MovableObjectButton.h"

#define TRIANGLE { Vector2(-0.5, -0.28867513459), Vector2(0.5, -0.28867513459), Vector2(0, 0.57735026919) }

void core::levels::Level1::LoadLevel() {
	_lasers = {
		Laser(Vector2(15, 65), Vector2(0.5, 0.5))
	};

	_staticNonReflectivesElements = {
		Polygon({ Vector2(0, 0), Vector2(WIDTH/2, 0), Vector2(WIDTH/2, 100), Vector2(0, 100) }, true, Drawable::Color::WHITE, 0)
	};

	_staticReflectivesElements = {
	};
	
	_movableElements = {
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12*Vector2(1,1)),
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12*Vector2(1,1)),
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12*Vector2(1,1)),
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12 * Vector2(1,1)),
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12 * Vector2(1,1)),
		Polygon(TRIANGLE, true, Drawable::Color::WHITE, 1,Vector2(0,0),12 * Vector2(1,1)),
	};

	Polygon sensorShape = Rectangle(Vector2(130, 10), Vector2(140, 20));
	sensorShape._color = Drawable::Color::GREEN;
	_sensor = Sensor(sensorShape);

	Level::LoadLevel();
}